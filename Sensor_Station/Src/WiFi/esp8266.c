#include "esp8266.h"

extern UART_HandleTypeDef huart1;
#define H_UART &huart1


volatile uint8_t rx_byte;

char buffer_tx[256];


uint8_t rx_buffer[256];
uint8_t rx_buffer_pointer = 0;

enum wifi_keywords_enum {
	WIFI_OK,
	WIFI_ERROR,
	WIFI_BUSY,
	WIFI_FAIL,
	WIFI_CON,
	WIFI_DIS,
	WIFI_READY,
	WIFI_N
};


const char wifi_keywords[WIFI_N][20] = {
	"OK\r\n",
	"ERROR\r\n",
	"BUSY\r\n",
	"FAIL\r\n",
	"CONNECTED\r\n",
	"DISCONNECT\r\n",
	"OK\r\n> "
};

volatile uint8_t wifi_flags[WIFI_N] = {0};
volatile uint8_t wifi_counter[WIFI_N] = {0};


void WiFi_Init(void) {
	HAL_UART_Receive_IT( H_UART, &rx_byte, 1 );
}


void HAL_UART_RxCpltCallback( UART_HandleTypeDef *huart ) { // Input char parsing
		rx_buffer[rx_buffer_pointer] = rx_byte;
		rx_buffer_pointer++;
		if ( rx_buffer_pointer == sizeof(rx_buffer) )
			rx_buffer_pointer = 0;

		for (int i = 0; i < WIFI_N; i++ ) {
			if ( rx_byte == wifi_keywords[i][ wifi_counter[i] ] ) {
				wifi_counter[i]++;
				if (wifi_keywords[i][ wifi_counter[i] ] == '\n') {
					wifi_flags[i] = 1;
					break;
				}
			} else {
				wifi_counter[i] = 0;
			}
		}
	HAL_UART_Receive_IT( H_UART, &rx_byte, 1 );
}



uint8_t WiFi_Wait_Response( uint16_t timeout ) {
	for (int i = 0; i < timeout; i++ ) {
		if ( wifi_flags[ WIFI_OK ] )
			return WIFI_STATUS_OK;
		if ( wifi_flags[ WIFI_ERROR ] )
			return WIFI_STATUS_ERROR;
		if ( wifi_flags[ WIFI_BUSY ] )
			return WIFI_STATUS_BUSY;
		if ( wifi_flags[ WIFI_FAIL ] )
			return WIFI_STATUS_FAIL;
		HAL_Delay(100);
	}
	return WIFI_STATUS_TIMEOUT;
}


void WiFi_Clear_Flags(void) {
	for ( int i = 0; i < WIFI_N; i++ )
		wifi_flags[i] = 0;	
}


void WiFi_Flags(void) {
	printf( "Flags:\r\n" );		
	for ( int i = 0; i < WIFI_N; i++ )
		if (wifi_flags[i])
			printf( "> %s",&wifi_keywords[i][0] );	
	printf( "-----\r\n" );		
}



void HAL_UART_ErrorCallback( UART_HandleTypeDef *huart ) {
//	volatile UART_HandleTypeDef *h = huart;
//	while (1) {
//		HAL_GPIO_TogglePin( GPIOE, GPIO_PIN_15 );
//		if (huart->Instance == &huart1)
//			HAL_Delay(100);
//
//
//	};
};



void WiFi_Connect(void) {

	printf("1 \r\n");
	HAL_GPIO_WritePin( WIFI_RESET_GPIO_Port, WIFI_RESET_Pin, GPIO_PIN_SET );
	printf("2 \r\n");
	HAL_Delay(1500);
	printf("3 \r\n");
	WiFi_Clear_Flags();
	printf("4 \r\n");
	WiFi_Init();
	//HAL_UART_Receive_IT( H_UART, &rx_byte, 1 );


	Display_Text("inter",40,0);
	Display_Refresh();


	//printf("5 \r\n");
	//Console_Output();
	HAL_Delay(400);
	printf("6 \r\n");


	sprintf( buffer_tx, "AT+CWMODE=1\r\n" );
	HAL_UART_Transmit( &huart1, (uint8_t*)buffer_tx, strlen(buffer_tx), 100 );
	//WiFi_Wait_Response(100);
	printf("Client mode - %d \r\n", WiFi_Wait_Response(100) );

	WiFi_Clear_Flags();
	#define AP_NAME "A.S.Tech Zyxel"
	#define AP_PASSWORD "areyougonnadie"
	//#define AP_NAME "LG_v10"
	//#define AP_PASSWORD "12345678"
	sprintf( buffer_tx, "AT+CWJAP=\"%s\",\"%s\"\r\n", AP_NAME, AP_PASSWORD );
	HAL_UART_Transmit( &huart1, (uint8_t*)buffer_tx, strlen(buffer_tx), 100 );
	uint8_t response = WiFi_Wait_Response(80);
	printf("Connect to AP - %d \r\n", response );

	if ( response == 0 ) { // connected succesfully

		WiFi_Clear_Flags();
		sprintf( buffer_tx, "AT+CIPMUX=1\r\n" );
		HAL_UART_Transmit( &huart1, (uint8_t*)buffer_tx, strlen(buffer_tx), 100 );
		printf("Multi-conn - %d \r\n", WiFi_Wait_Response(100) );

		//HAL_Delay(1000);

		WiFi_Clear_Flags();
		sprintf( buffer_tx, "AT+CIPSTART=0,\"UDP\",\"91.226.136.155\",123,123,0\r\n" );
		HAL_UART_Transmit( &huart1, (uint8_t*)buffer_tx, strlen(buffer_tx), 100 );
		printf("UDP - %d\r\n", WiFi_Wait_Response(100) );

		WiFi_Clear_Flags();
		sprintf( buffer_tx, "AT+CIPSEND=0,48\r\n" );
		HAL_UART_Transmit( &huart1, (uint8_t*)buffer_tx, strlen(buffer_tx), 100 );
		printf("Prepare - %d\r\n", WiFi_Wait_Response(100) );

	} else {
		printf("Failed \r\n");

	}

#define NTP_PACKET_SIZE 48
uint8_t buffer_ntp[NTP_PACKET_SIZE];

		memset( buffer_ntp, 0, sizeof(buffer_ntp) );
		buffer_ntp[0] = 0xE3;
		buffer_ntp[1] = 0;
		buffer_ntp[2] = 6;
		buffer_ntp[3] = 0xEC;
		buffer_ntp[12] = 49;
		buffer_ntp[13] = 0x4E;
		buffer_ntp[14] = 49;
		buffer_ntp[15] = 52;
		HAL_UART_Transmit( &huart1, (uint8_t*)buffer_ntp, sizeof(buffer_ntp), 100 );

		HAL_Delay(1000);

		uint32_t highWord = rx_buffer[(uint8_t)(rx_buffer_pointer-48+40)] *256 + rx_buffer[(uint8_t)(rx_buffer_pointer-48+41)];
		uint32_t lowWord  = rx_buffer[(uint8_t)(rx_buffer_pointer-48+42)] *256 + rx_buffer[(uint8_t)(rx_buffer_pointer-48+43)];
		uint32_t secsSince1900 = highWord << 16 | lowWord;
		uint32_t seventyYears = 2208988800UL;
		uint32_t epoch = secsSince1900 - seventyYears;

	//	OLED_Clear();

		//tick2 = HAL_GetTick();
		//sprintf( str, "dt: %d \r\n", tick2 - tick1 );
		//OLED_Print( str, 0, 24 );

		printf("Time: %d:%02d:%02d \r\n", (epoch % 86400) / 3600, (epoch % 3600) / 60, epoch % 60 );
		//OLED_Print( str, 0, 8 );

//
//		while(1) {
//			HAL_Delay(200);
//			LED( LED_RED, 1 );
//			HAL_Delay(200);
//			LED( LED_RED, 0 );
//		}


}












/*
void HAL_UART_RxCpltCallback( UART_HandleTypeDef *huart ) {
	
	uint8_t command = 0;
	
	//HAL_GPIO_WritePin( GPIOE, GPIO_PIN_15, GPIO_PIN_SET );

	if (rx_byte == '>')
		tx_ready_flag = 1;
	
	// Parse input byte
	switch (ipd_counter) {
		case 0:	if (rx_byte == '+') ipd_counter++; else ipd_counter = 0; break;
		case 1:	if (rx_byte == 'I') ipd_counter++; else ipd_counter = 0; break;
		case 2:	if (rx_byte == 'P') ipd_counter++; else ipd_counter = 0; break;
		case 3:	if (rx_byte == 'D') ipd_counter++; else ipd_counter = 0; break;
		case 4:	if (rx_byte == ',') ipd_counter++; else ipd_counter = 0; break;
		case 5:	ipd_counter++;  break;
		case 6:	if (rx_byte == ',') ipd_counter++; else ipd_counter = 0; break;
		case 7:	ipd_counter++;  break;
		case 8:	if (rx_byte == ':') ipd_counter++; else ipd_counter = 0; break;
		case 9:	command = rx_byte; ipd_counter = 0; break;
	};
	
	// Parse busy state
	switch (busy_counter) {
		case 0:	if (rx_byte == 'b') busy_counter++; else busy_counter = 0; break;
		case 1:	if (rx_byte == 'u') busy_counter++; else busy_counter = 0; break;
		case 2:	if (rx_byte == 's') busy_counter++; else busy_counter = 0; break;
		case 3:	if (rx_byte == 'y') busy_counter++; else busy_counter = 0; break;
		case 4:	tx_busy_flag = 1; busy_counter = 0; break;
	};

	// Parse OK
	switch (tx_send_ok_counter) {
		case 0:	if (rx_byte == 'O' ) tx_send_ok_counter++; else tx_send_ok_counter = 0; break;
		case 1:	if (rx_byte == 'K' ) tx_send_ok_counter++; else tx_send_ok_counter = 0; break;
		case 2:	if (rx_byte == '\r') tx_send_ok_counter++; else tx_send_ok_counter = 0; break;
		case 3:	if (rx_byte == '\n') tx_send_ok_flag = 1; tx_send_ok_counter = 0; break;
	};

	// Parse FAIL
	switch (tx_send_fail_counter) {
		case 0:	if (rx_byte == 'F' ) tx_send_fail_counter++; else tx_send_fail_counter = 0; break;
		case 1:	if (rx_byte == 'A' ) tx_send_fail_counter++; else tx_send_fail_counter = 0; break;
		case 2:	if (rx_byte == 'I' ) tx_send_fail_counter++; else tx_send_fail_counter = 0; break;
		case 3:	if (rx_byte == 'L' ) tx_send_fail_flag = 1; tx_send_fail_counter = 0; break;
	};
	
	
	// Process received command: Toggle LED
	if (command) {
		if ((command >= '0') && (command <= '7'))
			HAL_GPIO_TogglePin( GPIOE, GPIO_PIN_8 << (command -'0') );			
		if (command == '9')
			send_request ^= 1;
		command = 0;
	}; 
	
	HAL_UART_Receive_IT(huart,&rx_byte,1);
	
	//HAL_GPIO_WritePin( GPIOE, GPIO_PIN_15, GPIO_PIN_RESET );

};
*/



	
void ESP8266_Init(void) {
	
	
	/*
	char str[100];
	HAL_Delay(100);		
	
	// Change baudrate
	sprintf(str, "AT+CIOBAUD=%d\r\n",ESP8266_BAUDRATE);
	HAL_UART_Transmit(H_UART,(uint8_t*)str,strlen(str), HAL_MAX_DELAY );	
	*H_UART.Init.BaudRate = ESP8266_BAUDRATE;
  HAL_UART_Init(H_UART);
	HAL_UART_Receive_IT(H_UART,&rx_byte,1);	
	HAL_Delay(100);	
	
	// Multiple connections
	sprintf(str,"AT+CIPMUX=1\r\n");
	HAL_UART_Transmit(H_UART,(uint8_t*)str,strlen(str), HAL_MAX_DELAY );
	HAL_Delay(100);
	
	// Start UDP
	sprintf(str,"AT+CIPSTART=1,\"UDP\",\"192.168.4.1\",%d,%d,2\r\n",ESP8266_PORT,ESP8266_PORT);
	HAL_UART_Transmit(H_UART,(uint8_t*)str,strlen(str), HAL_MAX_DELAY );

	for (int i = 0; i < 8; i++) {
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_14);
		HAL_Delay(100);
	}	
	*/
	
}


void ESP8266_Send(uint8_t *buffer, uint16_t length) {

	/*
	char str[100];
	
	tx_ready_flag = 0;
	tx_busy_flag = 0;
	sprintf(str, "AT+CIPSEND=1,%d\r\n",length);
	
	do { // refactoring is desirable
		HAL_UART_Transmit_IT( H_UART, (uint8_t*)str, strlen(str) );	
		while ((!tx_ready_flag) && (!tx_busy_flag)) {};
	} while (tx_busy_flag);
	
	tx_send_ok_flag = 0;
	tx_send_fail_flag = 0;
	HAL_UART_Transmit_IT(H_UART,buffer,length );
	
	while (( !tx_send_ok_flag ) && (!tx_send_fail_flag))  {};
	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_15);	
*/
}
