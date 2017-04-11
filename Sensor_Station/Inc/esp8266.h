#ifndef _ESP8266_H
#define _ESP8266_H

#include "stm32f1xx_hal.h"
#include "string.h"


extern uint8_t rx_buffer[256];
extern uint8_t rx_buffer_pointer;

enum wifi_status {
	WIFI_STATUS_OK,
	WIFI_STATUS_ERROR,
	WIFI_STATUS_BUSY,
	WIFI_STATUS_FAIL,
	WIFI_STATUS_TIMEOUT
};

void WiFi_Init(void);
uint8_t WiFi_Wait_Response( uint16_t timeout );
void WiFi_Clear_Flags(void);

#endif


