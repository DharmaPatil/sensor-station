#ifndef _SENSORS_H
#define _SENSORS_H

#include "stm32f1xx_hal.h"

#define LED_GREEN          0
#define LED_RED            1

uint8_t Button(uint8_t button_number);
uint8_t LED(uint8_t led, uint8_t state );
uint8_t Baro_Test( void );
float CO2_Sensor( void );
void Sound( uint8_t enabled );

#endif

