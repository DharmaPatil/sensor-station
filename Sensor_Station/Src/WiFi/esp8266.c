#include "esp8266.h"

uint8_t rx_byte;
uint8_t rx_buffer[256];
uint8_t rx_buffer_pointer = 0;

enum wifi_status {
	WIFI_STATUS_OK,
	WIFI_STATUS_ERROR,
	WIFI_STATUS_BUSY,
	WIFI_STATUS_FAIL,
	WIFI_STATUS_TIMEOUT
};

enum wifi_keywords_enum {
	WIFI_OK,
	WIFI_ERROR,
	WIFI_BUSY,
	WIFI_FAIL,
	WIFI_CON,
	WIFI_DIS,
	WIFI_READY,
	WIFI_N
};

const char wifi_keywords[WIFI_N][20] = {
	"OK\r\n",
	"ERROR\r\n",
	"BUSY\r\n",
	"FAIL\r\n",
	"CONNECTED\r\n",
	"DISCONNECT\r\n",
	"OK\r\n> "
};

volatile uint8_t wifi_flags[WIFI_N] = {0};
volatile uint8_t wifi_counter[WIFI_N] = {0};


void WiFi_Init(void) {
	HAL_UART_Receive_IT(H_UART, &rx_byte, 1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	rx_buffer[rx_buffer_pointer] = rx_byte;
	rx_buffer_pointer++;
	if (rx_buffer_pointer == sizeof(rx_buffer))
		rx_buffer_pointer = 0;
	for (int i = 0; i < WIFI_N; i++ ) {
		if (rx_byte == wifi_keywords[i][ wifi_counter[i] ]) {
			wifi_counter[i]++;
			if (wifi_keywords[i][ wifi_counter[i] ] == '\n') {
				wifi_flags[i] = 1;
				break;
			}
		} else {
			wifi_counter[i] = 0;
		}
	}
	HAL_UART_Receive_IT(H_UART, &rx_byte, 1);
}


uint8_t WiFi_Wait_Response(uint16_t timeout) {
	for (int i = 0; i < timeout; i++) {
		if (wifi_flags[ WIFI_OK ] )
			return WIFI_STATUS_OK;
		if (wifi_flags[ WIFI_ERROR ])
			return WIFI_STATUS_ERROR;
		if (wifi_flags[ WIFI_BUSY ])
			return WIFI_STATUS_BUSY;
		if (wifi_flags[ WIFI_FAIL ])
			return WIFI_STATUS_FAIL;
		HAL_Delay(100);
	}
	return WIFI_STATUS_TIMEOUT;
}


void WiFi_Clear_Flags(void) {
	for (int i = 0; i < WIFI_N; i++)
		wifi_flags[i] = 0;	
}


void WiFi_Get_Flags(void) {
	printf("Flags:\r\n");
	for (int i = 0; i < WIFI_N; i++)
		if (wifi_flags[i])
			printf("> %s",&wifi_keywords[i][0]);
	printf("-----\r\n");
}


void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart) {
}


void WiFi_Send_Command(const char *s) {
	HAL_UART_Transmit(H_UART, (uint8_t*)s, strlen(s), 1000);
}

void WiFi_Send_Message(uint8_t *buf, uint8_t len) {
	HAL_UART_Transmit(H_UART, buf, len, 1000);
}

	

