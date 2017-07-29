#include "settings.h"

static uint8_t Scanf_w_Quotes(char *str, char *field, char *value);
//static uint32_t Settings_CRC(network_settings_t *s);


static FIL file;

/*
uint8_t Settings_Load_from_Flash(network_settings_t *s) {
	uint8_t i;
	memcpy(s, (int*)SETTINGS_ADDRESS, sizeof(network_settings_t));
	if (s->crc == Settings_CRC(s)) {
		// display settings
		for (i = 0; i < WIFI_MAX_NUM; i++) {
			printf("SSID %d: \"%s\" \n", i+1, &(s->ssid[i][0]) );
			printf("Password %d: %d* \n", i+1, strlen(&(s->pass[i][0])));
			printf("\n");
		}
		for (i = 0; i < SERVER_MAX_NUM; i++) {
			printf("Server %d: %s \n", i+1, &(s->server[i][0]) );
		}
		printf("\n");
		printf("Timezone: %d\n", s->timezone );
		printf("\n");
		return 0;
	} else {
		memset(s, 0, sizeof(network_settings_t));
		return 1;
	}
}*/

/*
uint8_t Settings_Save_to_Flash(network_settings_t *s) {
	uint32_t i;
	uint32_t page_error;
	FLASH_EraseInitTypeDef page_erase;
	HAL_FLASH_Unlock();
	page_erase.NbPages = 1;
	page_erase.PageAddress = SETTINGS_ADDRESS;
	page_erase.Banks = 0;
	page_erase.TypeErase = FLASH_TYPEERASE_PAGES;
	HAL_FLASHEx_Erase(&page_erase, &page_error);
	s->crc = Settings_CRC(s);
	for (i = 0; i < sizeof(network_settings_t)/4; i++)
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, SETTINGS_ADDRESS+i*4, *((uint32_t*)s+i));
	HAL_FLASH_Lock();
	return 0;
}*/


uint8_t Settings_Load_from_File(network_settings_t *s) {
	char str[STR_MAX_LEN*2+10];
	char field[STR_MAX_LEN];
	char value[STR_MAX_LEN];
	volatile FRESULT fr;

	memset(s, 0, sizeof(network_settings_t));
  fr = f_open(&file, SETTINGS_FILENAME, FA_READ);
	if (fr == FR_OK) {
		while(!f_eof(&file)) {
			f_gets(str, sizeof(str), &file);
			Scanf_w_Quotes(str, field, value);
			if (strcmp(field, SSID_STRING) == 0)
				strcpy(s->ssid, value);
			if (strcmp(field, PASSWORD_STRING) == 0)
				strcpy(s->password, value);
			if (strcmp(field, SERVER_STRING) == 0)
				strcpy(s->server, value);
			if (strcmp(field, TIMEZONE_STRING) == 0)
				s->timezone = atoi(value);
		}
	}
  f_close(&file);
	return fr;
}





/*
uint8_t Settings_Save_to_File(network_settings_t *s) {
	FRESULT fr;
	int res;
	int i;
	fr = f_open(&file, SETTINGS_FILENAME, FA_WRITE|FA_CREATE_ALWAYS);
	for (i = 0; i < WIFI_MAX_NUM; i++) {
		res = f_printf(&file, "%s %d \"%s\"\n", SSID_STRING, i+1, &(s->ssid[i][0]) );
		res = f_printf(&file, "%s %d \"\"\n", PASSWORD_STRING, i+1  );
	}
	for (i = 0; i < SERVER_MAX_NUM; i++) {
		res = f_printf(&file, "%s %d \"%s\"\n", SERVER_STRING, i+1, &(s->server[i][0]) );
	}
	res = f_printf(&file, "%s %d\n", TIMEZONE_STRING, s->timezone );
	f_close(&file);
	return fr;
}


uint8_t Settings_Synchronize(network_settings_t *s, network_settings_t *s_new) {
	uint8_t changed = 0;
	if (s->timezone != s_new->timezone) {
		s->timezone = s_new->timezone;
		changed = 1;
		printf("Timezone updated: %d \n", (int)(s->timezone));
		printf("\n");
	}
	for (int i = 0; i < WIFI_MAX_NUM; i++) {
		if (strcmp(&(s->ssid[i][0]), &(s_new->ssid[i][0])) != 0) { // new ssid
			strcpy(&(s->ssid[i][0]), &(s_new->ssid[i][0]));
			strcpy(&(s->pass[i][0]), &(s_new->pass[i][0]));
			changed = 1;
			printf("Network %d updated: \n", i+1);
			printf("ssid: \"%s\" \n", &(s->ssid[i][0]));
			printf("pass: \"%s\" \n", &(s->pass[i][0]));
			printf("\n");
		} else { // same ssid
			if (s_new->pass[i][0] != '\0') { // password exists
				strcpy(&(s->pass[i][0]), &(s_new->pass[i][0]));
				changed = 1;
				printf("Network %d updated: \n", i+1);
				printf("ssid: \"%s\" \n", &(s->ssid[i][0]));
				printf("pass: \"%s\" \n", &(s->pass[i][0]));
				printf("\n");
			}
		}
	}
	for (int i = 0; i < SERVER_MAX_NUM; i++) {
		if (strcmp(&(s->server[i][0]), &(s_new->server[i][0])) != 0) {
			strcpy(&(s->server[i][0]), &(s_new->server[i][0]));
			changed = 1;
			printf("Server %d updated: \n", i+1);
			printf("%s \n", &(s->server[i][0]));
			printf("\n");
		}
	}
	return changed;
}
*/


static uint8_t Scanf_w_Quotes(char *str, char *field, char *value ) {
	char *q1, *q2;
	int len;
	char pattern[10];
	sprintf(pattern, "%%%ds", STR_MAX_LEN-1 );
	sscanf(str, pattern, field);
	//sscanf(str, "%s %d  ", field, n);
	*value = '\0';
	q1 = str;
	while ((*q1 != '\0') && (*q1 != '\"'))
		q1++;
	if (*q1 == '\0') { // no quotes
		q2 = q1;
		len = 0;
	} else { // quote found
		q2 = q1+1;
		while ((*q2 != '\0') && (*q2 != '\"'))
			q2++;
		len = (int)(q2 - q1) - 1;
		if (len >= STR_MAX_LEN)
			len = STR_MAX_LEN - 1;
		memcpy(value, q1+1, len);
	}
	value[len] = '\0';
	return 0;
}


/*
static uint32_t Settings_CRC(network_settings_t *s) {
	return HAL_CRC_Calculate(&hcrc, (uint32_t*)s, sizeof(network_settings_t)/4 - 1);
}
*/
