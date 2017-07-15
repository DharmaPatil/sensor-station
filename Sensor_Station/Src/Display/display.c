#include "display.h"

uint8_t screen_buffer[1024];
const Font_TypeDef* font;

#include "fonts/font_small.c"
#include "fonts/font_medium.c"
#include "fonts/font_large.c"
#include "fonts/font_ultra.c"
#include "fonts/font_times.c"
#include "images/image_status.c"
#include "images/image_cloud.c"

static void Software_I2C_Init(void);
static void Display_Send_Cmd(uint8_t command);
static void Display_Send_Byte(uint8_t val);


void Display_Text(char *str, uint8_t x, uint8_t y) {
	char *c = str;
	while (*c != 0) {
		if ((*c >= font->first_char) && (*c <= font->last_char)) {
			uint16_t char_start_index = font->indexes[*c - font->first_char];
			uint16_t char_stop_index = font->indexes[*c - font->first_char+1];
			for (int col = char_start_index; col < char_stop_index; col++) { 
				uint64_t column_src = 0;
				uint64_t column_txt = 0;		
				for (int j = 0; j < font->height; j++)
					*(((uint8_t*)&column_txt)+j) = (font->bitmaps[col*font->height+j]) & 0xFF;   			
				column_txt <<= y;	
				memcpy(&column_src, &screen_buffer[x*8], 8);
				column_src |= column_txt;
				memcpy(&screen_buffer[x*8], &column_src, 8);
				x++;
				if (x >= 128) break;
			}	
		}
		if (*c == ' ') {
			x+=2*font->height;
		} else {
			x++;
		}
		x++;
		if (x >= 128) break;
		c++;
	}
}


void Display_Image(const uint8_t *image, uint8_t x, uint8_t y) {
	uint8_t i;
	uint8_t img_height, img_width;
	img_width = image[0];
	img_height = image[1];
	for ( i = 0; i < img_width; i++ ) {
		uint64_t column_src = 0;
		uint64_t column_img = 0;		
		for ( int j = 0; j < img_height; j++ )
			*(((uint8_t*)&column_img)+j) = ( image[i*img_height+j+2]) & 0xFF;   			
		column_img <<= y;	
		memcpy(&column_src, &screen_buffer[x*8], 8);
		column_src |= column_img;
		memcpy(&screen_buffer[x*8], &column_src, 8);
		x++;
		if (x >= 128) break;
	}
}


void Display_Clear(void) {
	memset(screen_buffer, 0, 1024);
}


void Display_Refresh(void) {
  uint16_t i;	
  Display_Send_Cmd(0xA6);  // Set Normal Display
  Display_Send_Cmd(0xB0);  // Set page address to 0
  Display_Send_Cmd(0x40);  // Display start line register to 0
  Display_Send_Cmd(0x00);  // Set low col address to 0
  Display_Send_Cmd(0x10);  // Set high col address to 0
	for(i = 0; i < 1024; i++) // fill the display's RAM with graphic... 128*64 pixel picture
		Display_Send_Byte(screen_buffer[i]);
}


void Display_Init(void) {
	Software_I2C_Init();
	HAL_Delay(20);
	Display_Send_Cmd(0xAE); // Disable
  Display_Send_Cmd(0x2E); //deactivate scrolling
  Display_Send_Cmd(0xA4); //Set all pixels OFF
  Display_Send_Cmd(0x20); //Set Memory Addressing Mode
  Display_Send_Cmd(0x01); //Set Memory Addressing Mode to Page addressing mode(RESET)
	Display_Send_Cmd(0x8D); // Charge pump settings
	Display_Send_Cmd(0x14); // Enable charge pump
	Display_Send_Cmd(0x1B); // Enable charge pump
	if (DISPLAY_FLIP_X)
		Display_Send_Cmd(0xA1); // Right to Left
	else
		Display_Send_Cmd(0xA0); // Left to right
	if (DISPLAY_FLIP_Y)
		Display_Send_Cmd(0xC0); // Upside down
	else
		Display_Send_Cmd(0xC8); // Upside up
	Display_Send_Cmd(0x81); // Brightness
	Display_Send_Cmd(DISPLAY_BRIGHTNESS);
	Display_Clear();
	Display_Refresh();
	Display_Send_Cmd(0xAF); // Enable
}


// ************************************************************************************************************
// I2C general functions
// ************************************************************************************************************


void Software_I2C_Init(void) {
	HAL_GPIO_WritePin( SW_I2C_SCL_GPIO, SW_I2C_SCL_PIN, GPIO_PIN_SET );
	HAL_GPIO_WritePin( SW_I2C_SDA_GPIO, SW_I2C_SDA_PIN, GPIO_PIN_SET );
}


void Software_I2C_Start() {
	SW_I2C_DELAY;
	SW_I2C_SDA_GPIO->BRR = SW_I2C_SDA_PIN;
	SW_I2C_DELAY;
	SW_I2C_SCL_GPIO->BRR = SW_I2C_SCL_PIN;
	SW_I2C_DELAY;
}


void Software_I2C_Stop(void) {
	SW_I2C_SCL_GPIO->BRR = SW_I2C_SCL_PIN;
	SW_I2C_SDA_GPIO->BRR = SW_I2C_SDA_PIN;
	SW_I2C_DELAY;
	SW_I2C_SCL_GPIO->BSRR = SW_I2C_SCL_PIN;
	SW_I2C_DELAY;
	SW_I2C_SDA_GPIO->BSRR = SW_I2C_SDA_PIN;	
	SW_I2C_DELAY;
	SW_I2C_DELAY;
	SW_I2C_DELAY;
}


void Software_I2C_Write(uint8_t data) {
	uint8_t i;
	
	for (i = 0; i < 8; i++) {
		if (data & 0x80)
			SW_I2C_SDA_GPIO->BSRR = SW_I2C_SDA_PIN;
		else
			SW_I2C_SDA_GPIO->BRR = SW_I2C_SDA_PIN;
		data <<= 1;
		
		SW_I2C_DELAY;
		SW_I2C_SCL_GPIO->BSRR = SW_I2C_SCL_PIN;
		SW_I2C_DELAY;
		SW_I2C_SCL_GPIO->BRR = SW_I2C_SCL_PIN;
	}
	
	SW_I2C_SDA_GPIO->BSRR = SW_I2C_SDA_PIN;
	SW_I2C_DELAY;
	SW_I2C_SCL_GPIO->BSRR = SW_I2C_SCL_PIN;
	SW_I2C_DELAY;
	SW_I2C_SCL_GPIO->BRR = SW_I2C_SCL_PIN;
	SW_I2C_DELAY;
}


void Display_Send_Cmd(uint8_t command) {
  Software_I2C_Start();
	Software_I2C_Write(0x78);
  Software_I2C_Write(0x80);
  Software_I2C_Write(command);
  Software_I2C_Stop();
}


void Display_Send_Byte(uint8_t val) {
  Software_I2C_Start();
	Software_I2C_Write(0x78); 
  Software_I2C_Write(0x40);
  Software_I2C_Write(val);
  Software_I2C_Stop();	
}

