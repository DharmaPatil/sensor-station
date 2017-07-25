#ifndef WIFI_H
#define WIFI_H

#include "stm32f1xx_hal.h"
#include "esp8266.h"
#include "../Display/display.h"

uint8_t WiFi_Connect_to_AP(char *ssid, char *password);
uint8_t WiFi_Synchronize_Time(char *server, RTC_TimeTypeDef *s_time);

#endif
