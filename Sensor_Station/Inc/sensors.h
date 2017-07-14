#ifndef SENSORS_H
#define SENSORS_H

#include "stm32f1xx_hal.h"

char MS5611_Conversion(float *pressure);
char TGS4161_Conversion(float *emf);
char DHT22_Conversion(uint8_t num, float *temperature, float *humidity);

#endif
