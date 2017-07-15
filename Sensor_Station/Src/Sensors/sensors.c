#include "sensors.h"

extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim2;
extern DMA_HandleTypeDef hdma_tim2_ch3;
extern DMA_HandleTypeDef hdma_tim2_ch2_ch4;
extern I2C_HandleTypeDef hi2c2;

#define BARO_ADDRESS 0xEF  // 0xEE // 111011Cx


char MS5611_Conversion(float *pressure) {

	uint8_t data[5] = { 0, 0, 0, 0, 0 };	
	signed long long int c[7];
	signed long long int d[3];
	
	for (int i = 0; i < 7; i++) {
		data[0] = 0xA0 | (i<<1);
		HAL_I2C_Master_Transmit( &hi2c2, BARO_ADDRESS, data, 1, HAL_MAX_DELAY );
		HAL_I2C_Master_Receive( &hi2c2, BARO_ADDRESS, data+1, 2, HAL_MAX_DELAY );
		c[i] = data[1]*256 + data[2];
	}
	
	data[0] = 0x48; // D1 - 4096
	HAL_I2C_Master_Transmit( &hi2c2, BARO_ADDRESS, data, 1, HAL_MAX_DELAY );
	HAL_Delay(12);
	data[0] = 0x00;
	HAL_I2C_Master_Transmit( &hi2c2, BARO_ADDRESS, data, 1, HAL_MAX_DELAY );
	HAL_I2C_Master_Receive( &hi2c2, BARO_ADDRESS, data+1, 3, HAL_MAX_DELAY );
	d[1] = (data[1]*256 + data[2])*256 + data[3];
	
	data[0] = 0x58; // D2 - 4096
	HAL_I2C_Master_Transmit( &hi2c2, BARO_ADDRESS, data, 1, HAL_MAX_DELAY );
	HAL_Delay(12);
	data[0] = 0x00;
	HAL_I2C_Master_Transmit( &hi2c2, BARO_ADDRESS, data, 1, HAL_MAX_DELAY );
	HAL_I2C_Master_Receive( &hi2c2, BARO_ADDRESS, data+1, 3, HAL_MAX_DELAY );
	d[2] = (data[1]*256 + data[2])*256 + data[3];
	
	signed long long int dT;
	signed long long int temp;
	
	signed long long int OFF;
	signed long long int SENS;
	signed long long int p;
	
	signed long long int T2;
	signed long long int OFF2;
	signed long long int SENS2;
	
	dT = d[2] - c[5]*(1<<8);
	temp = 2000 + (dT*c[6])/(1<<23);
	
	OFF = c[2]*(1<<16) + (c[4]*dT)/(1<<7);
	SENS = c[1]*(1<<15) + (c[3]*dT)/(1<<8);
	
	OFF2 = 0;
	SENS2 = 0;
	
	if ( temp < 2000 ) {
		T2 = (dT*dT)/(1<<31);
		OFF2 = 5*(temp-2000)*(temp-2000)/2;
		SENS2 = 5*(temp-2000)*(temp-2000)/4;
	}
	
	if ( temp < -1500 ) {
		OFF2 = OFF2 + 7*(temp+1500)*(temp+1500);
		SENS2 = SENS2 + 11*(temp+1500)*(temp+1500)/2;
	}
	
	OFF = OFF - OFF2;
	SENS = SENS - SENS2;
	
	p = ( d[1]*SENS/(1<<21)-OFF ) / (1<<15);

	double p_mm = 750.0617 * p / 100000; 

	*pressure = (float)p_mm;
	
	return 0;
}




char TGS4161_Conversion( float *emf ) {
	int sum = 0;
	for (int i = 0; i < 10; i++) {
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, 3000);
		sum += HAL_ADC_GetValue(&hadc1);
		HAL_Delay(2);
	}
	*emf = ((float)sum)/10 * 3.3f/4096;
	return 0;
}




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
	





