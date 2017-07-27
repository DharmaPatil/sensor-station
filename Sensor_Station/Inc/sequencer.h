#ifndef SEQUENCER_H
#define SEQUENCER_H

#include "includes.h"

#define SEQ_BASE_FREQ 440

#define SEQ_VOLUME_LOW  50
#define SEQ_VOLUME_HIGH  80

#define SEQ_TIMER         htim3
#define SEQ_CHANNEL       TIM_CHANNEL_4
#define SEQ_REGISTER      CCR4

#define TIMER_FREQ 1000000

#define SEQ_SEMITONE 1.05946309436f

#define SEQ_STEP_LENGTH 1//100

void Sequencer_Init(void);
void Sequencer_Tick(void);
void Sequencer_Start(void);



#endif
