#include "settings.h"


static uint8_t Scanf_w_Quotes(char *str, char *field, char *value, int *n);
static uint8_t Settings_Load_from_File(network_settings_t *s);
static uint8_t Settings_Save_to_File(network_settings_t *s);


network_settings_t settings;
network_settings_t settings_new;


FIL file;


void Settings_Update(void) {
	// called from main cycle
	//uint8_t changed = 0;
	//Settings_Load_from_Flash(&settings);
	Settings_Load_from_File(&settings_new);
	//changed = Settings_Synchronize(&settings, &settings_new);
	//if (changed) {
	Settings_Save_to_File(&settings_new);
	//	Settings_Save_to_Flash(&settings);
	//}
	return;
}


//static uint8_t Settings_Load_from_Flash(network_settings_t *s) {
//	// todo
//	return 0;
//}
//
//static uint8_t Settings_Load_from_Flash(network_settings_t *s) {
//	// todo
//	return 0;
//}

static uint8_t Settings_Load_from_File(network_settings_t *s) {
	char str[WIFI_MAX_LEN*2+10];
	char field[WIFI_MAX_LEN];
	char value[WIFI_MAX_LEN];
	volatile FRESULT fr;
	memset(s, 0, sizeof(network_settings_t));
  fr = f_open(&file, SETTINGS_FILENAME, FA_READ);
  printf("Open: %d \r\n", fr);
	if (fr == FR_OK) {
		while(!f_eof(&file)) {
			int n;
			f_gets(str, sizeof(str), &file);
			Scanf_w_Quotes(str, field, value, &n);
			if (strcmp(field, SSID_STRING) == 0)
				strcpy(s->ssid[n-1], value);
			if (strcmp(field, PASSWORD_STRING) == 0)
				strcpy(s->pass[n-1], value);
			if (strcmp(field, SERVER_STRING) == 0)
				strcpy(s->server[n-1], value);
			if (strcmp(field, TIMEZONE_STRING) == 0)
				s->timezone = n;
		}
	}
  f_close(&file);
	return fr;
}


static uint8_t Settings_Save_to_File(network_settings_t *s) {
	FRESULT fr;
	int i;
	fr = f_open(&file, SETTINGS_FILENAME, FA_WRITE | FA_CREATE_ALWAYS);
	for (i = 0; i < WIFI_MAX_NUM; i++) {
		f_printf(&file, "%s %d \"%s\"\n", SSID_STRING, i+1, &(s->ssid[i][0]) );
		f_printf(&file, "%s %d \"\"\n", PASSWORD_STRING, i+1, &(s->pass[i][0]) );
	}
	for (i = 0; i < SERVER_MAX_NUM; i++) {
		f_printf(&file, "%s %d \"%s\"\n", SERVER_STRING, i+1, &(s->server[i][0]) );
	}
	f_printf(&file, "%s %d\n", TIMEZONE_STRING, s->timezone );
	f_close(&file);
	return fr;
}



//static uint8_t Settings_Synchronize(network_settings_t *s, network_settings_t *s_new) {
//	uint8_t changed = 0;
//	int i;
//	if (s->timezone != s_new->timezone) {
//		s->timezone = s_new->timezone;
//		changed = 1;
//	}
//	for (i = 0; i < WIFI_MAX_NUM; i++) {
//		if (strcmp(s->ssid[i], s_new->ssid[i])) {
//			strcpy(s->ssid[i], s_new->ssid[i]);
//			strcpy(s->pass[i], s_new->pass[i]);
//			changed = 1;
//		} else {
//			s_new->ssid[i][0] = '\0';
//			strcpy(s->pass[i], s_new->pass[i]);
//			changed = 1;
//		}
//	}
//	for (i = 0; i < SERVER_MAX_NUM; i++) {
//		if (strcmp(s->server[i], s_new->server[i])) {
//			strcpy(s->server[i], s_new->server[i]);
//			changed = 1;
//		}
//	}
//	return changed;
//}


static uint8_t Scanf_w_Quotes(char *str, char *field, char *value, int *n) {
	char *q1, *q2;
	int len;
	sscanf(str, "%s %d  ", field, n);
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
		memcpy(value, q1+1, len);
	}
	value[len] = '\0';
	return 0;
}


