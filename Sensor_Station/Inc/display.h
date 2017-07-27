#ifndef DISPLAY_H
#define DISPLAY_H
#include "includes.h"

typedef const struct {
	const char first_char;
	const char last_char;
	const char height;
	const uint16_t *indexes;
	const uint8_t *bitmaps;
} Font_TypeDef;

extern const Font_TypeDef* font;
extern const Font_TypeDef font_small;
extern const Font_TypeDef font_small_plus;
extern const Font_TypeDef font_medium;
extern const Font_TypeDef font_large;
extern const Font_TypeDef font_ultra;
extern const Font_TypeDef font_times;
extern const uint8_t image_status[];
extern const uint8_t image_cloud[];

void Display_Init(void);
void Display_Clear(void);
void Display_Text(char *str, uint8_t x, uint8_t y);
void Display_Image(const uint8_t *image, uint8_t x, uint8_t y);
void Display_Erase(uint8_t x, uint8_t y, uint8_t w, uint8_t h);
void Display_Refresh(void);

#endif
