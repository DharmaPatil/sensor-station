#ifndef INTERFACE_H
#define INTERFACE_H

#include "stm32f1xx_hal.h"

#define LED_GREEN          0
#define LED_RED            1

uint8_t Button(uint8_t button_number);
uint8_t LED(uint8_t led, uint8_t state );

#endif

