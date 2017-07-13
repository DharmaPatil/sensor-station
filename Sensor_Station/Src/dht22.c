#include "dht22.h"

extern TIM_HandleTypeDef htim2;
extern DMA_HandleTypeDef hdma_tim2_ch3;
extern DMA_HandleTypeDef hdma_tim2_ch2_ch4;


char DHT22_Conversion(uint8_t num, float *temperature, float *humidity) {
	
	GPIO_InitTypeDef GPIO_InitStruct_1;
	GPIO_InitTypeDef GPIO_InitStruct_2;
	uint16_t tim_data[50];
	uint8_t result[5];
	uint16_t temp16; 
	uint16_t hum16;
	uint8_t valid;
	
	uint16_t dht22_pin;
	GPIO_TypeDef *dht22_port;
	uint32_t dht22_tim_ch;
	DMA_HandleTypeDef *dht22_dma;
			
	if ( num == 0 ) {
		dht22_pin = DHT22_INT_Pin;
		dht22_port = DHT22_INT_GPIO_Port;
		dht22_tim_ch = TIM_CHANNEL_3;
		dht22_dma = &hdma_tim2_ch3;
	} else {
		dht22_pin = DHT22_EXT_Pin;
		dht22_port = DHT22_EXT_GPIO_Port;
		dht22_tim_ch = TIM_CHANNEL_4;
		dht22_dma = &hdma_tim2_ch2_ch4;	
	}
					
	HAL_GPIO_WritePin( dht22_port, dht22_pin, GPIO_PIN_SET );	
	GPIO_InitStruct_1.Pin = dht22_pin;
	GPIO_InitStruct_1.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct_1.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(dht22_port, &GPIO_InitStruct_1);	
	HAL_GPIO_WritePin( dht22_port, dht22_pin, GPIO_PIN_RESET );	
	HAL_Delay(3);	
	HAL_GPIO_WritePin( dht22_port, dht22_pin, GPIO_PIN_SET );	
	
	// init as a alternative function
	GPIO_InitStruct_2.Pin = dht22_pin;
	GPIO_InitStruct_2.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct_2.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(dht22_port, &GPIO_InitStruct_2);	
	
	HAL_TIM_Base_Start( &htim2 );
	HAL_TIM_IC_Start_DMA( &htim2, dht22_tim_ch, (uint32_t *)tim_data, 42 );
	HAL_DMA_PollForTransfer( dht22_dma, HAL_DMA_FULL_TRANSFER, 10 );
	HAL_TIM_IC_Stop_DMA( &htim2, dht22_tim_ch );
			
	for (int i = 0; i < 41; i++ ) {
		tim_data[i] = tim_data[i+1] - tim_data[i];
	}
	
	for ( int byte = 0; byte < 5; byte++ ) {
		result[byte] = 0;
		for (int bit = 0; bit < 8; bit++) {
			result[byte]<<=1;
			if ( tim_data[byte*8+bit+1] > 105 )
				result[byte] |= 1;
		}
	}
			
	temp16 = ((result[2]&0x7F)<<8) + result[3];
	hum16 = (result[0]<<8) + result[1];

	*temperature = ((float)temp16)/10;
	*humidity = ((float)hum16)/10;
	valid = ((((result[0]+result[1]+result[2]+result[3])&0xFF) == result[4] ) && (dht22_dma->Instance->CNDTR == 0) );
	
	return valid;
	
}
	
