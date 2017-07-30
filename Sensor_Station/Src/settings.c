#include "settings.h"

static uint8_t Scanf_w_Quotes(char *str, char *field, char *value);
static uint32_t Settings_CRC(network_settings_t *s);


static FIL file;


uint8_t Settings_Load_from_Flash(network_settings_t *s) {
	memcpy(s, (int*)SETTINGS_ADDRESS, sizeof(network_settings_t));
	if (s->crc == Settings_CRC(s)) {
		return 0;
	} else {
		memset(s, 0, sizeof(network_settings_t));
		return 1;
	}
}


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
}


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






uint8_t Settings_Synchronize(network_settings_t *s, network_settings_t *s_new) {
	uint8_t changed = 0;
	if (s->timezone != s_new->timezone) {
		s->timezone = s_new->timezone;
		changed = 1;
		printf("Timezone updated: %d \n", (int)(s->timezone));
	}

	if (strcmp(s->ssid, s_new->ssid) != 0) {
		if (strlen(s_new->ssid) != 0) {
			strcpy(s->ssid, s_new->ssid);
			changed = 1;
			printf("SSID updated: \n");
			printf("%s \n", s->ssid);
		}
	}

	if (strcmp(s->password, s_new->password) != 0) {
		if (strlen(s_new->password) != 0) {
			strcpy(s->password, s_new->password);
			changed = 1;
			printf("Password updated: \n");
			printf("%s \n", s->password);
		}
	}

	if (strcmp(s->server, s_new->server) != 0) {
		if (strlen(s_new->server) != 0) {
			strcpy(s->server, s_new->server);
			changed = 1;
			printf("Server updated: \n");
			printf("%s \n", s->server);
		}
	}
	return changed;
}


void Settings_Display(network_settings_t *s) {
	printf("SSID: %s \n", s->ssid);
	printf("Password: %d* \n", strlen(s->password));
	printf("Server: %s \n", s->server);
	printf("Time zone: %d \n", s->timezone);
};








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


static uint32_t Settings_CRC(network_settings_t *s) {
	return HAL_CRC_Calculate(&hcrc, (uint32_t*)s, sizeof(network_settings_t)/4 - 1);
}
