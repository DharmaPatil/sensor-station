#include "console.h"

#define CONSOLE_LINES 8
#define CONSOLE_CHARS 40
#define CONSOLE_FONT  font_small

static char console_array[CONSOLE_LINES][CONSOLE_CHARS+1] = {0,};
static uint8_t c_line = 0;
static uint8_t c_char = 0;
static uint8_t scroll = 0;


void Console_Print_Char(char c) {
	console_array[c_line][c_char] = c;
	c_char++;
	if (c_char == CONSOLE_CHARS) {
		c_char = 0;
		c_line++;
	}
	if (c == '\n') {
		console_array[c_line][c_char] = 0;
		c_line++;
		c_char = 0;
	}
	if (c_line >= CONSOLE_LINES) {
		c_line = 0;
		c_char = 0;
		scroll = 1;
	}
}


void Console_Output(void) {
	font = &CONSOLE_FONT;
	for (int i = 0; i < 1; i++) {
		console_array[i][CONSOLE_CHARS] = 0;
		Display_Text(&console_array[i][0], 0, 0);
		Display_Refresh();
	}
}




