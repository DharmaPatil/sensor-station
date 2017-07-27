#ifndef SD_CARD_H
#define SD_CARD_H

#include "includes.h"

#define SD_SECTOR_SIZE 512

uint8_t SD_Init(void);
uint8_t SD_Read_Sector(uint32_t n,uint8_t *buf);
uint8_t SD_Write_Sector(uint32_t n,uint8_t *buf);


#endif



