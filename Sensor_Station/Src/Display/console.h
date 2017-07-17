#ifndef CONSOLE_H
#define CONSOLE_H

#include "stm32f1xx_hal.h"
#include <string.h>
#include "display.h"

void Console_Print_Char(char c);
void Console_Output(void);

#endif
