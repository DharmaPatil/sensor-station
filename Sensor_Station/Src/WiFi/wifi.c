#include "wifi.h"


uint8_t WiFi_Connect_to_AP(char *ssid, char *password) {
	uint8_t res;
	HAL_GPIO_WritePin(WIFI_RESET_GPIO_Port, WIFI_RESET_Pin, GPIO_PIN_SET);
	HAL_Delay(1000);
	WiFi_Clear_Flags();
	HAL_Delay(500);
	WiFi_Send_Command("AT+CWMODE=1\r\n");
	res = WiFi_Wait_Response(100);
	printf("Client mode - %d \r\n", res);
	WiFi_Clear_Flags();
	WiFi_Send_Command("AT+CWJAP=\"");
	WiFi_Send_Command(ssid);
	WiFi_Send_Command("\",\"");
	WiFi_Send_Command(password);
	WiFi_Send_Command("\"\r\n");
	res = WiFi_Wait_Response(100);
	printf("Connect to AP - %d \r\n", res );
	return res;
}


uint8_t WiFi_Synchronize_Time(char *server, RTC_TimeTypeDef *s_time) {
	uint8_t buffer_ntp[48];
	uint8_t res;
	WiFi_Clear_Flags();
	WiFi_Send_Command("AT+CIPMUX=1\r\n");
	res = WiFi_Wait_Response(10);
	printf("Multi-conn - %d \r\n", res);
	WiFi_Clear_Flags();
	WiFi_Send_Command("AT+CIPSTART=0,\"UDP\",\"");
	WiFi_Send_Command(server);
	WiFi_Send_Command("\",123,123,0\r\n");
	printf("UDP - %d\r\n", WiFi_Wait_Response(100));
	WiFi_Clear_Flags();
	WiFi_Send_Command("AT+CIPSEND=0,48\r\n");
	printf("Prepare - %d\r\n", WiFi_Wait_Response(100));
	memset( buffer_ntp, 0, sizeof(buffer_ntp) );
	buffer_ntp[0] = 0xE3;
	buffer_ntp[1] = 0;
	buffer_ntp[2] = 6;
	buffer_ntp[3] = 0xEC;
	buffer_ntp[12] = 49;
	buffer_ntp[13] = 0x4E;
	buffer_ntp[14] = 49;
	buffer_ntp[15] = 52;
	WiFi_Send_Message(buffer_ntp, sizeof(buffer_ntp));
	HAL_Delay(1000);
	uint32_t highWord = rx_buffer[(uint8_t)(rx_buffer_pointer-48+40)] *256 + rx_buffer[(uint8_t)(rx_buffer_pointer-48+41)];
	uint32_t lowWord  = rx_buffer[(uint8_t)(rx_buffer_pointer-48+42)] *256 + rx_buffer[(uint8_t)(rx_buffer_pointer-48+43)];
	uint32_t secsSince1900 = highWord << 16 | lowWord;
	uint32_t seventyYears = 2208988800UL;
	uint32_t epoch = secsSince1900 - seventyYears;
	epoch += 3;
	s_time->Hours = (epoch % 86400) / 3600;
	s_time->Minutes = (epoch % 3600) / 60;
	s_time->Seconds = epoch % 60;
	return 0;
}




