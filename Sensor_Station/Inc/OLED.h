#ifndef __OLED_H
#define __OLED_H
#include "stm32f1xx_hal.h"
#include <string.h>

typedef struct {
	char first_char;
	char last_char;
	char height;
	const uint16_t *indexes;
	const uint8_t *bitmaps;
} Font_TypeDef;


extern const Font_TypeDef* font;
extern const Font_TypeDef font_small;
extern const Font_TypeDef font_medium;
extern const Font_TypeDef font_large;
extern const Font_TypeDef font_ultra;
extern const Font_TypeDef font_times;
extern const uint8_t image_status[];
extern const uint8_t image_cloud[];


#define SW_I2C_SCL_GPIO  OLED_SCL_GPIO_Port
#define SW_I2C_SCL_PIN   OLED_SCL_Pin

#define SW_I2C_SDA_GPIO  OLED_SDA_GPIO_Port
#define SW_I2C_SDA_PIN   OLED_SDA_Pin

#define SW_I2C_DELAY  { __nop(); __nop(); __nop(); __nop(); __nop(); __nop(); }

#define OLED_FLIP_X      0
#define OLED_FLIP_Y      0
#define OLED_BRIGHTNESS  255


void OLED_Init(void);
void OLED_Clear(void);
void OLED_Print( char *str, uint8_t x, uint8_t y );
void OLED_Image( const uint8_t *image, uint8_t x, uint8_t y );
void OLED_Clear_Buffer(void);

#endif
