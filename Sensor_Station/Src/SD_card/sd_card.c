#include "sd_card.h"

extern SPI_HandleTypeDef hspi1;

uint8_t buffer[SD_SECTOR_SIZE];		

uint32_t memory_size = 0;
uint32_t card_capacity = 0;
	
uint8_t SDHC;     
uint8_t SD_version;

//extern int fputc(int c, FILE *f);

#define CS_ENABLE         { HAL_GPIO_WritePin( SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET); } 
#define CS_DISABLE    	  { HAL_GPIO_WritePin( SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET );  }	
		
#define GO_IDLE_STATE       0   // reboot
#define SEND_IF_COND        8   // for SDC V2 check voltage
#define READ_SINGLE_BLOCK   17  // read block
#define WRITE_SINGLE_BLOCK  24  // write block
#define SD_SEND_OP_COND     41  // start initialization
#define APP_CMD             55  // ACMD
#define READ_OCR            58  // read OCR		


uint8_t buffer_00[SD_SECTOR_SIZE];
uint8_t buffer_FF[SD_SECTOR_SIZE];


uint8_t spi_transfer(uint8_t data_tx) { 
	uint8_t data_rx;
	HAL_SPI_TransmitReceive( &hspi1, &data_tx, &data_rx, 1, 20 );
  return data_rx;
}

uint8_t spi_transfer_buffer(uint8_t *data_tx, uint8_t *data_rx) { 
	if ( data_rx == 0 )
		data_rx = buffer_00;
	if ( data_tx == 0 )
		data_tx = buffer_FF;	
	HAL_SPI_TransmitReceive( &hspi1, data_tx, data_rx, SD_SECTOR_SIZE, 200 );
  return 0;
}


uint8_t SD_Send_Command(uint8_t cmd, uint32_t arg) {
  uint8_t response, wait = 0, tmp;     

  if ( SDHC == 0 )// for SD - address correction (byte), for SDHC - not (pages)
		if ( cmd == READ_SINGLE_BLOCK || cmd == WRITE_SINGLE_BLOCK )  
			arg = arg<<9;
  CS_ENABLE;
  spi_transfer(cmd|0x40);
  spi_transfer(arg>>24);
  spi_transfer(arg>>16);
  spi_transfer(arg>>8);
  spi_transfer(arg);

	if ( cmd == GO_IDLE_STATE )      
		spi_transfer(0x95); // valid CRC7
  else 
		if ( cmd == SEND_IF_COND )  
			spi_transfer(0x87); // valid CRC7
		else 
			spi_transfer(0x01); // dummy CRC7
	
  while ( ( response = spi_transfer(0xFF) ) == 0xFF ) {
   if ( wait++ > 0xFE ) 
		 break; 
	}

  if ( response == 0x00 && cmd == 58 ) {
    tmp = spi_transfer(0xFF);       
    if ( tmp & 0x40 ) 
			SDHC = 1;
    else              
			SDHC = 0;
    spi_transfer(0xFF); 
    spi_transfer(0xFF); 
    spi_transfer(0xFF); 
  }
  spi_transfer(0xFF);
  CS_DISABLE; 
  return response;
}
		


uint8_t SD_Read_Register( uint8_t cmd, uint8_t* buf ) {
  //uint8_t* dst = reinterpret_cast<uint8_t*>(buf);
	uint8_t retry;
	uint8_t buffer[16];
	
	
  if ( SD_Send_Command(cmd, 0) )
    return 1;
	CS_ENABLE;
	
	retry = 0;
	while ( spi_transfer(0xFF)!= 0xFE ) {
		retry++;
		if ( retry > 100 ) {
			CS_DISABLE;
			return 1;
		}
	}
	
  for (uint16_t i = 0; i < 16; i++) {
		//buffer[i] = spi_transfer(0xFF);
		//printf( "%02X ", buffer[i] = spi_transfer(0xFF) );
	}
	//printf( "\r\n" );
	
	if ( SDHC ) {
		memory_size = (buffer[9] + (buffer[8]<<8) + ((buffer[7]<<16)&0xF) ) * 512 / 1024;
		card_capacity = (buffer[9] + (buffer[8]<<8) + ((buffer[7]<<16)&0xF) ) * 512 * (1024 / SD_SECTOR_SIZE);
	} else {
		uint32_t c_size = ( (buffer[8]>>6) & 0x03 ) + (buffer[7]<<2) + ((buffer[6]&0x3)<<10);  // 73:62
		uint32_t c_size_mult = ( (buffer[9]&0x01)<<2 ) + ( (buffer[10]>>6)&0x03 );               // 49:47
		uint32_t read_bl_len = buffer[5] & 0xF; // 83:80
		uint32_t bl_len = 1 << read_bl_len;
		uint32_t mult = 1 << ( c_size_mult + 2 );
		uint32_t blocknr = ( c_size + 1 ) * mult;
		memory_size = blocknr * bl_len / 1024 / 1024;
		card_capacity = blocknr * bl_len / SD_SECTOR_SIZE;
	}
	
	// CSD Register
	if ( cmd == 9 )	{
		//printf( "Size: %d Mb \r\n", memory_size );
		//printf( "Sectors: %d \r\n", card_capacity );
	};
	
  spi_transfer(0xFF);  // get first crc byte
  spi_transfer(0xFF);  // get second crc byte

	CS_DISABLE;
	return 0;
}




uint8_t SD_Init(void) {
  uint8_t   i;
  uint8_t   response;	 
  uint16_t  retry = 0;    
	
	CS_DISABLE;
	HAL_Delay(5);
	
  for ( i = 0; i < 10; i++ ) 
		spi_transfer(0xFF); 
 
  CS_ENABLE;
  while ( ( response = SD_Send_Command( GO_IDLE_STATE, 0 ) ) != 0x01 ) {      
		HAL_Delay(1);
    if ( retry++ > 0x20 )  {
			//printf("Idle: %d \r\n",response);
			return 1;  	
		}
	}
  CS_DISABLE;
  spi_transfer (0xFF);
  spi_transfer (0xFF);
	HAL_Delay(5);
	
  retry = 0;  
	SD_version = 2;
  while( ( response = SD_Send_Command( SEND_IF_COND, 0x000001AA ) ) != 0x01 ) { 
		HAL_Delay(1);
    if ( retry++ > 0xFE ) { 
      SD_version = 1;
      break;
    } 
  }
	char str[40];
  sprintf(str, "Ver: %d \r\n",SD_version);
	Display_Text(str, 0, 48);
	Display_Refresh();

	retry = 0;                                     
	do {
		response = SD_Send_Command( APP_CMD, 0 ); 
		//printf( "App: %02X ", response );
		response = SD_Send_Command( SD_SEND_OP_COND, 0x40000000 );
		//printf( "Op-cond: %02X  \r\n", response );
		retry++;
		if ( retry > 0xFFE ) 
			return 1;  	 
	} while ( response != 0x00 );                      

  CS_DISABLE;
 
	retry = 0;
	SDHC = 0;
	if ( SD_version == 2 ) { 
		while ( SD_Send_Command( READ_OCR, 0 ) != 0x00 )
		if ( retry++ > 0xFE )  
			break;
	}
	sprintf(str,"SDHC: %d \r\n",SDHC);
  //sprintf(str, "Ver: %d \r\n",SD_version);
	Display_Text(str, 0, 32);
	Display_Refresh();
	
	uint8_t b[16];
	SD_Read_Register(9,b);
	//SD_Read_Register(10,b);
	

	sprintf(str,"Mem: %d \r\n",memory_size);
	Display_Text(str, 0, 16);
	Display_Refresh();

	sprintf(str,"Cap: %d \r\n",card_capacity);
	Display_Text(str, 0, 0);
	Display_Refresh();


	memset( buffer_00, 0x00, SD_SECTOR_SIZE );
	memset( buffer_FF, 0xFF, SD_SECTOR_SIZE );
	
	hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
	HAL_SPI_Init(&hspi1);
	
	return 0; 
}
	
		

uint8_t SD_Read_Sector(uint32_t n,uint8_t *buf) { 
  uint16_t i = 0;
  if ( SD_Send_Command( READ_SINGLE_BLOCK, n ) ) 
		return 1;  
  CS_ENABLE;
  while ( spi_transfer(0xFF) != 0xFE )                
		if ( i++ > 0xFFFE) {
			CS_DISABLE; 
			return 1;
		}

	//for ( i = 0; i < SD_SECTOR_SIZE; i++ ) 
	//	*buf++ = spi_transfer(0xFF);
	spi_transfer_buffer( 0, buf );		
		
  spi_transfer(0xFF); 
  spi_transfer(0xFF); 
  spi_transfer(0xFF); 
  return 0;
}
		
		

uint8_t SD_Write_Sector(uint32_t n,uint8_t *buf) {
  uint8_t     response;
  uint16_t    i, wait = 0;
  if ( SD_Send_Command( WRITE_SINGLE_BLOCK, n ) ) 
		return 1;
  CS_ENABLE;
  spi_transfer(0xFE);    
  //for ( i = 0; i < SD_SECTOR_SIZE; i++ ) 
	//	spi_transfer(*buf++);
  
	spi_transfer_buffer( buf, 0 );	
	
	spi_transfer(0xFF); 
  spi_transfer(0xFF);
  response = spi_transfer(0xFF);
  if ( (response & 0x1F) != 0x05) { 
		CS_DISABLE; 
		return 1; 
	}
  while ( !spi_transfer(0xFF) )  
  if ( wait++ > 0xFFFE )
	{
		CS_DISABLE; 
		return 1;
	}
  CS_DISABLE;
  spi_transfer(0xFF);   
  CS_ENABLE;         
  while ( !spi_transfer(0xFF) ) 
  if ( wait++ > 0xFFFE ) {
		CS_DISABLE; 
		return 1;
	}
  CS_DISABLE;
  return 0;
}





