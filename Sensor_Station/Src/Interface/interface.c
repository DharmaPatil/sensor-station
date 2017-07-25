#include "interface.h"

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


uint8_t LED(uint8_t state ) {
	if (state)
		*(&LED_TIMER.Instance->CCR4) = 15;
	else
		*(&LED_TIMER.Instance->CCR4) = 0;
	HAL_TIM_PWM_Start( &LED_TIMER, TIM_CHANNEL_4 );
	return 1;
}

