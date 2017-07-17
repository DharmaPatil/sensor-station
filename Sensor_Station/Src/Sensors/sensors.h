#ifndef SENSORS_H
#define SENSORS_H

#include "stm32f1xx_hal.h"

char MS5611_Conversion(int *pressure);
char TGS4161_Conversion(int *emf);
char DHT22_Conversion(uint8_t num, int *temperature, int *humidity);

#endif
