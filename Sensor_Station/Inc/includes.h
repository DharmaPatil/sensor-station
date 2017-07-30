#include "stm32f1xx_hal.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "types.h"

#include "fatfs.h"
#include "types.h"

#include "display.h"
#include "console.h"

#include "sd_card.h"
#include "settings.h"

#include "esp8266.h"
#include "wifi.h"
#include "time.h"

#include "sensors.h"
#include "files.h"

#include "interface.h"
#include "sequencer.h"

extern UART_HandleTypeDef huart1;
extern RTC_HandleTypeDef hrtc;
extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim2;
extern DMA_HandleTypeDef hdma_tim2_ch3;
extern DMA_HandleTypeDef hdma_tim2_ch2_ch4;
extern I2C_HandleTypeDef hi2c2;
extern SPI_HandleTypeDef hspi1;
extern TIM_HandleTypeDef htim3;

extern uint8_t console_mode;

extern CRC_HandleTypeDef hcrc;

