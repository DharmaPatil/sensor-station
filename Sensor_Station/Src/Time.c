#include "Time.h"

extern RTC_HandleTypeDef hrtc;
RTC_TimeTypeDef rtc_time;

volatile uint8_t rtc_interrupt_flag = 0;

//uint8_t RTC_ByteToBcd(uint8_t Value) {
//  uint32_t bcdhigh = 0;
//  while(Value >= 10) {
//    bcdhigh++;
//    Value -= 10;
//  }
//  return  ((uint8_t)(bcdhigh << 4) | Value);
//}

void Time_Start_Interrupts(void) {
	HAL_RTCEx_SetSecond_IT( &hrtc );
}


void Time_Set_Protection(uint8_t protection) {
	if (protection)	
		__HAL_RTC_WRITEPROTECTION_ENABLE(&hrtc);
	else
		__HAL_RTC_WRITEPROTECTION_DISABLE(&hrtc);
	
}


void Time_Get_Time(uint8_t *time) {
	rtc_interrupt_flag = 0;
	while ( !rtc_interrupt_flag );
	rtc_interrupt_flag = 0;
	HAL_RTC_GetTime( &hrtc, &rtc_time, RTC_FORMAT_BIN );
	time[0] = rtc_time.Hours;
	time[1] = rtc_time.Minutes;
	time[2] = rtc_time.Seconds;
}


void HAL_RTCEx_RTCEventCallback( RTC_HandleTypeDef* hrtc ) {
	rtc_interrupt_flag = 1;
}




