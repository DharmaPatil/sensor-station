#include "console.h"

#define CONSOLE_LINES 4
#define CONSOLE_CHARS 32
#define CONSOLE_FONT  font_medium

static char console_array[CONSOLE_LINES][CONSOLE_CHARS+1] = {0,};
static uint8_t c_line = 0;
static uint8_t c_char = 0;
static uint8_t scroll = 0;

int __io_putchar(int ch) {
	Console_Print_Char(ch);
	return ch;
}

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
		Console_Output();
	}
	if (c_line >= CONSOLE_LINES) {
		c_line = 0;
		c_char = 0;
		scroll = 1;
	}
}


void Console_Output(void) {
	font = &CONSOLE_FONT;
	uint8_t i_line;
	uint8_t y_display;
	Display_Clear();
	for (int i = 0; i < CONSOLE_LINES; i++) {
		i_line = (i+c_line*scroll) % CONSOLE_LINES;
		y_display = 64 - 64/CONSOLE_LINES*(i+1);
		console_array[i][CONSOLE_CHARS] = 0;
		Display_Text(&console_array[i_line][0], 0, y_display );
	}
	Display_Refresh();
}




