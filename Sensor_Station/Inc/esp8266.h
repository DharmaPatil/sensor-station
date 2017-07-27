#ifndef ESP8266_H
#define ESP8266_H

#include "includes.h"

#define H_UART &huart1

extern uint8_t rx_buffer[256];
extern uint8_t rx_buffer_pointer;

void WiFi_Init(void);
void WiFi_Clear_Flags(void);
void WiFi_Get_Flags(void);
uint8_t WiFi_Wait_Response(uint16_t timeout);
void WiFi_Send_Command(const char *s);
void WiFi_Send_Message(uint8_t *buf, uint8_t len);



#endif


