#ifndef _TIME_H
#define _TIME_H

#include "stm32f1xx_hal.h"

void Time_Set_Protection(uint8_t protection);
void Time_Start_Interrupts(void);
void Time_Get_Time(uint8_t* time);

#endif
