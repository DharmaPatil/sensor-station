#include "Sensors.h"

#define LED_TIMER          htim4
extern TIM_HandleTypeDef   LED_TIMER;


uint8_t Button(uint8_t button_number) {
	uint8_t result;
	switch (button_number) {
		case 1:
			result = !HAL_GPIO_ReadPin( BUTTON_1_GPIO_Port, BUTTON_1_Pin );
			break;
		case 2:
			result = !HAL_GPIO_ReadPin( BUTTON_2_GPIO_Port, BUTTON_2_Pin );
			break;
		default:
			result = 0;
			break;
	}
	return result;
}


uint8_t LED(uint8_t led, uint8_t state ) {
	switch (led) {
		case LED_GREEN :
			if (state)
				*(&LED_TIMER.Instance->CCR3) = 90;
			else
				*(&LED_TIMER.Instance->CCR3) = 0;
			break;
		case LED_RED :
			if (state)
				*(&LED_TIMER.Instance->CCR4) = 15;
			else
				*(&LED_TIMER.Instance->CCR4) = 0;
			break;	
	}
	HAL_TIM_PWM_Start( &LED_TIMER, TIM_CHANNEL_3 );
	HAL_TIM_PWM_Start( &LED_TIMER, TIM_CHANNEL_4 );
	return 1;
}



extern I2C_HandleTypeDef hi2c2;

uint8_t Baro_Test( void ) {
	uint8_t data[10];
	#define BARO_ADDRESS 0xEF  // 0xEE // 111011Cx	
	HAL_I2C_Master_Transmit( &hi2c2, BARO_ADDRESS, data, 2, HAL_MAX_DELAY );
	return 0;
}


extern ADC_HandleTypeDef hadc1;

float CO2_Sensor( void ) {
	float emf;
//	int sum = 0;
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, 3000);
	emf = (float)(HAL_ADC_GetValue(&hadc1)) * 3.3/4096;
	return emf;
}

extern TIM_HandleTypeDef htim3;

void Sound( uint8_t enabled ) {
	if (enabled) 
		HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
	else
		HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_4);
}























