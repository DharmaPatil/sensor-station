#include "ms5611.h"

extern I2C_HandleTypeDef hi2c2;

#define BARO_ADDRESS 0xEF  // 0xEE // 111011Cx

char MS5611_Conversion(float *pressure) {

	uint8_t data[5] = { 0, 0, 0, 0, 0 };	
	signed long long int c[7];
	signed long long int d[3];
	
	for ( int i = 0; i < 7; i++ ) {
		data[0] = 0xA0 | ( i<<1 );
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