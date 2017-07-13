#ifndef DHT22_H
#define DHT22_H

#include "stm32f1xx_hal.h"

char DHT22_Conversion(uint8_t num, float *temperature, float *humidity);

#endif
