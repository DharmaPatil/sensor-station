#ifndef SETTINGS_H
#define SETTINGS_H

#include "includes.h"

#define SSID_STRING      "ssid"
#define PASSWORD_STRING  "password"
#define SERVER_STRING    "server"
#define TIMEZONE_STRING  "timezone"

#define STR_MAX_LEN 32

#define SETTINGS_FILENAME "settings.txt"

typedef struct {
	char ssid[STR_MAX_LEN];
	char password[STR_MAX_LEN];
	char server[STR_MAX_LEN];
	signed int timezone;
	unsigned int status;
	unsigned int crc;
} network_settings_t;


uint8_t Settings_Load_from_File(network_settings_t *s);

uint8_t Settings_Load_from_Flash(network_settings_t *s);
uint8_t Settings_Save_to_Flash(network_settings_t *s);

uint8_t Settings_Synchronize(network_settings_t *s, network_settings_t *s_new);

void Settings_Display(network_settings_t *s);


//#define WIFI_MAX_NUM  2
//#define WIFI_MAX_LEN  32
//#define SERVER_MAX_NUM   2
//#define SERVER_MAX_LEN   16
//
#define SETTINGS_ADDRESS    (0x08000000 + 64*1024 - 1024) // Last 1kB of flash



//uint8_t Settings_Save_to_File(network_settings_t *s);


//#if ( (size network_settings_t) > FLASH_PAGE_SIZE )
//	#error "Network settings struct too large"
//#endif

#endif
