#ifndef TIME_H
#define TIME_H

#include "includes.h"

void Time_Set_Protection(uint8_t protection);

void Time_Start_Interrupts(void);
void Time_Poll_Interrupts(void);

void Time_Get_Time(uint8_t* time);

void Date_Decode(uint32_t secs, uint32_t *date);

#endif
