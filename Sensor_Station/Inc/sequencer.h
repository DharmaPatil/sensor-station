#ifndef _SEQUENCER_H
#define _SEQUENCER_H

#include "stm32f1xx_hal.h"
#include <math.h>

#define SEQ_BASE_FREQ 440

#define SEQ_VOLUME_LOW  50
#define SEQ_VOLUME_HIGH  80

extern TIM_HandleTypeDef  htim3;
#define SEQ_TIMER         htim3
#define SEQ_CHANNEL       TIM_CHANNEL_4
#define SEQ_REGISTER      CCR4

#define TIMER_FREQ 1000000

#define SEQ_SEMITONE 1.05946309436f

#define SEQ_STEP_LENGTH 1//100

void Sequencer_Init( void );
void Sequencer_Tick( void );
void Sequencer_Start( char *seq );

uint8_t Sequencer_Get_Next( uint8_t *note, uint8_t *length );


#endif
