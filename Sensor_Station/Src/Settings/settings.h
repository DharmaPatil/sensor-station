#ifndef SETTINGS_H
#define SETTINGS_H

#include "stm32f1xx_hal.h"
#include "ff.h"
#include "string.h"


#define SSID_STRING      "ssid"
#define PASSWORD_STRING  "password"
#define SERVER_STRING    "server"
#define TIMEZONE_STRING  "timezone"

#define WIFI_MAX_NUM  2
#define WIFI_MAX_LEN  32
#define SERVER_MAX_NUM   2
#define SERVER_MAX_LEN   16

#define SETTINGS_FILENAME "settings.txt"

typedef struct {
	char ssid[WIFI_MAX_NUM][WIFI_MAX_LEN];
	char pass[WIFI_MAX_NUM][WIFI_MAX_LEN];
	char server[SERVER_MAX_NUM][SERVER_MAX_LEN];
	int timezone;
} network_settings_t; // must be < FLASH_PAGE_SIZE

void Settings_Update(void);



//#if ( (size network_settings_t) > FLASH_PAGE_SIZE )
//	#error "Network settings struct too large"
//#endif

#endif
