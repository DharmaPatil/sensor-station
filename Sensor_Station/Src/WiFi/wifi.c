//#include "wifi.h"
//
//
//extern UART_HandleTypeDef huart1;
//
//#define H_UART &huart1;
//
//
//

//		sprintf( str, "Reset WiFi" );
//		OLED_Print( str, 0, 8 );
//
//		HAL_GPIO_WritePin( WIFI_RESET_GPIO_Port, WIFI_RESET_Pin, GPIO_PIN_RESET );
//		HAL_Delay(1000);
//		HAL_GPIO_WritePin( WIFI_RESET_GPIO_Port, WIFI_RESET_Pin, GPIO_PIN_SET );
//		HAL_Delay(1000);
//
//		OLED_Clear();
//
//		WiFi_Clear_Flags();
//		sprintf( buffer_tx, "AT+CWMODE_CUR=2\r\n" );
//		HAL_UART_Transmit( &huart1, (uint8_t*)buffer_tx, strlen(buffer_tx), 100 );
//		sprintf( str, "Switch to AP - %d", WiFi_Wait_Response(100) );
//		OLED_Print( str, 0, 40 );
//
//
//		WiFi_Clear_Flags();
//		sprintf( buffer_tx, "AT+CWSAP=\"ESP_AP\",\"password\",8,3\r\n" );
//		HAL_UART_Transmit( &huart1, (uint8_t*)buffer_tx, strlen(buffer_tx), 100 );
//		sprintf( str, "Create AP - %d", WiFi_Wait_Response(100) );
//		OLED_Print( str, 0, 24 );
//
//		while(1) {
//			HAL_Delay(200);
//			LED( LED_RED, 1 );
//			HAL_Delay(200);
//			LED( LED_RED, 0 );



