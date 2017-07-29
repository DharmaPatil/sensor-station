#include "files.h"

static FIL file;
static char filename[20];
FILINFO fno;

int Files_Find_First_Availible(void) {
	FRESULT fr;
	for ( int i = 0; i < 100; i++ ) {
		sprintf(filename, "LOG_%03d.TXT", i);
		fr = f_stat((const char*)filename, &fno);
		printf("%s - %d \n", filename, fr);
		if ( fr == FR_OK ) {
			continue;
		} else {
			printf("%s - ready \n", filename);
			return i;
		}
	}
	return -1;
}


uint8_t File_Start() {
	FRESULT fr;
	Files_Find_First_Availible();
	fr = f_open(&file, (const char*)filename, FA_WRITE | FA_CREATE_NEW );
	printf("Open %s: %d \n", filename, fr);
	return fr;
}


uint8_t File_Write_Line(char *str) {
	FRESULT fr;
	int test;
	fr = f_write(&file, str, strlen(str), &test);
	f_sync(&file);
	printf("Write %s: %d \n", filename, fr);
	return fr;
}


uint8_t File_Stop(void) {
	FRESULT fr;
	fr = f_close(&file);
	printf("Close %s: %d \n", filename, fr);
	return fr;
}



//sprintf(str, "Write: %d\r\n", f_write(&testFile, testBuffer, 16, &testBytes) );
//Display_Text(str, 0, 16);
//sprintf(str, "Close: %d\r\n", );
//Display_Text(str, 0, 0);
//





