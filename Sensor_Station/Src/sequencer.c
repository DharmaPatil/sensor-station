#include "sequencer.h"

char scale[] = "A BC D EF G a bc d ef g -";
char *seq_pnt;
uint8_t seq_active = 0;
uint16_t seq_periods[25];
uint16_t seq_values[25];

char seq_ozzy[] = "2E 2- 2G 2- 1G 1- 1a 1- 2a 2- 1c 1b 1c 1b 1c 1b 1G 1- 2G 1a 1- 2a 2-";

static uint8_t Sequencer_Get_Next(uint8_t *note, uint8_t *length);


void Sequencer_Init(void) {
	float multiplier = 1;
	float frequency_f;
	float seq_period_f;
	float seq_value_f;
	float seq_volume_f;
	for ( int i = 0; i < 25; i++ ) {
		frequency_f = SEQ_BASE_FREQ * multiplier;
		seq_period_f = (float)TIMER_FREQ / frequency_f;
		seq_volume_f = (SEQ_VOLUME_HIGH - (float)i * ( SEQ_VOLUME_HIGH - SEQ_VOLUME_LOW ) / 24) / 200;
		seq_value_f = seq_period_f * seq_volume_f;
		seq_periods[i] = lroundf(seq_period_f) - 1;
		seq_values[i] = lroundf(seq_value_f) - 1;
		multiplier *= SEQ_SEMITONE;
	}
	seq_periods[24] = seq_periods[23];
	seq_values[24] = 0;
	SEQ_TIMER.Instance->ARR = seq_periods[24];
	SEQ_TIMER.Instance->SEQ_REGISTER = seq_values[24];
	HAL_TIM_PWM_Start( &SEQ_TIMER, SEQ_CHANNEL );
}


uint8_t Sequencer_Get_Next(uint8_t *note, uint8_t *length) {
	uint8_t i;
	*note = 0;
	*length = 0;
	while (!((*seq_pnt>='1')&&(*seq_pnt<='9'))) {
		if (*seq_pnt=='\0') 
			return 1;
		seq_pnt++;
	}
	*length = *seq_pnt - '0';
	seq_pnt++;
	for (i = 0; i < 26; i++)
		if (*seq_pnt == scale[i])
			*note = i;
	seq_pnt++;
	if (*seq_pnt == '#')
		(*note)++;
	//printf("N: %d, L: %d \r\n", *note, *length);
	return 0;
}


void Sequencer_Tick(void) {
	uint8_t length, note, result;
	static uint8_t countdown = 0;
	static uint8_t divider = 0;
	divider++;
	if (divider == SEQ_STEP_LENGTH) {
		divider = 0;
		if (seq_active) {
			if (countdown == 0) {
				result = Sequencer_Get_Next(&note, &length);
				if (result == 0) {
					SEQ_TIMER.Instance->SEQ_REGISTER = seq_values[note];
					SEQ_TIMER.Instance->ARR = seq_periods[note];
					countdown = length - 1;
				} else {
					seq_active = 0;
					SEQ_TIMER.Instance->SEQ_REGISTER = 0;
				}
			} else {
				countdown--;
			}
		}
	}
}


void Sequencer_Start(void) {
	seq_pnt = seq_ozzy;
	seq_active = 1;
}

