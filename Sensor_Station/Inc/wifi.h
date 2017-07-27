#ifndef WIFI_H
#define WIFI_H

#include "includes.h"

uint8_t WiFi_Connect_to_AP(char *ssid, char *password);
uint8_t WiFi_Synchronize_Time(char *server, RTC_TimeTypeDef *s_time, RTC_DateTypeDef *s_date);

#endif
