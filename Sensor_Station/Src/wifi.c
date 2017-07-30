#include "wifi.h"

extern network_settings_t settings;

uint8_t WiFi_Connect_to_AP(char *ssid, char *password) {
	uint8_t res;
	HAL_GPIO_WritePin(WIFI_RESET_GPIO_Port, WIFI_RESET_Pin, GPIO_PIN_SET);
	HAL_Delay(1000);
	WiFi_Clear_Flags();
	HAL_Delay(500);
	//WiFi_Send_Command("AT+CWMODE=1\r\n");
	//res = WiFi_Wait_Response(100);
	//printf("Client mode - %d \r\n", res);
	WiFi_Clear_Flags();
	WiFi_Send_Command("AT+CWJAP=\"");
	WiFi_Send_Command(ssid);
	WiFi_Send_Command("\",\"");
	WiFi_Send_Command(password);
	WiFi_Send_Command("\"\r\n");
	res = WiFi_Wait_Response(100);
	//printf("Connect to AP - %d \r\n", res );
	return res;
}


uint8_t WiFi_Synchronize_Time(char *server, RTC_TimeTypeDef *s_time, RTC_DateTypeDef *s_date) {
	uint8_t buffer_ntp[48];
	uint8_t res;
	uint32_t date[3];

	WiFi_Clear_Flags();
	WiFi_Send_Command("AT+CIPMUX=1\r\n");
	res = WiFi_Wait_Response(10);
	//printf("Multi-conn - %d \r\n", res);
	WiFi_Clear_Flags();
	WiFi_Send_Command("AT+CIPSTART=0,\"UDP\",\"");
	WiFi_Send_Command(server);
	WiFi_Send_Command("\",123,123,0\r\n");
	res = WiFi_Wait_Response(100);
	//printf("UDP - %d\r\n", res);
	WiFi_Clear_Flags();
	WiFi_Send_Command("AT+CIPSEND=0,48\r\n");
	res = WiFi_Wait_Response(100);
	//printf("Prepare - %d\r\n", res);
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
	uint32_t high_word = rx_buffer[(uint8_t)(rx_buffer_pointer-48+40)] *256 + rx_buffer[(uint8_t)(rx_buffer_pointer-48+41)];
	uint32_t low_word  = rx_buffer[(uint8_t)(rx_buffer_pointer-48+42)] *256 + rx_buffer[(uint8_t)(rx_buffer_pointer-48+43)];
	uint32_t seconds = high_word << 16 | low_word;
	seconds -= 2208988800UL;
	seconds += 3;
	seconds += settings.timezone*3600;

	WiFi_Clear_Flags();
	WiFi_Send_Command("AT+CIPCLOSE=0\r\n");
	//printf("Close - %d\r\n", WiFi_Wait_Response(100));

	Date_Decode(seconds, date);

	if ((date[2] < 2017) || (date[2] > 2030)) { // improbable date
		printf("Date error \n");
		return 1;
	} else {
		s_date->Date = date[0];
		s_date->Month = date[1];
		s_date->Year = date[2] - 2000;
		s_time->Hours = (seconds % 86400) / 3600;
		s_time->Minutes = (seconds % 3600) / 60;
		s_time->Seconds = seconds % 60;
		return 0;
	}
}




