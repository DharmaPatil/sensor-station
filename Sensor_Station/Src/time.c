#include "time.h"


RTC_TimeTypeDef rtc_time;

volatile uint8_t rtc_interrupt_flag = 0;


void Time_Start_Interrupts(void) {
	HAL_RTCEx_SetSecond_IT( &hrtc );
}


void Time_Poll_Interrupts(void) {
	while ( !rtc_interrupt_flag );
	rtc_interrupt_flag = 0;
}


void HAL_RTCEx_RTCEventCallback( RTC_HandleTypeDef* hrtc ) {
	rtc_interrupt_flag = 1;
}


uint8_t Leap_Year(uint32_t year) {
	if (year % 4) // 1999, 2001...
		return 0;
	else {
		if (!(year % 400)) // 2000
			return 1;
		else {
			if (!(year % 100)) // 2100
				return 0;
			else
				return 1; // 2004, 2008
		}
	}
}


void Date_Decode(uint32_t secs, uint32_t *date) {
	uint32_t day, month, year;
	uint32_t days;
	uint32_t days_in_year;
	uint32_t days_in_month;

	days = secs / 86400;
	year = 1970;
	while (1) {
		if (Leap_Year(year))
			days_in_year = 366;
		else
			days_in_year = 365;

		if (days >= days_in_year)
			days -= days_in_year;
		else
			break;
		year++;
	}
	for (month = 1; month <= 12; month++) {
		switch (month) {
		case 2:
			if (Leap_Year(year))
				days_in_month = 29;
			else
				days_in_month = 28;
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			days_in_month = 30;
			break;
		default:
			days_in_month = 31;
			break;
		}
		if (days >= days_in_month) {
			days -= days_in_month;
		}
		else {
			break;
		}
	}
	day = days + 1;
	date[0] = day;
	date[1] = month;
	date[2] = year;
}















//uint8_t RTC_ByteToBcd(uint8_t Value) {
//  uint32_t bcdhigh = 0;
//  while(Value >= 10) {
//    bcdhigh++;
//    Value -= 10;
//  }
//  return  ((uint8_t)(bcdhigh << 4) | Value);
//}



void Time_Set_Protection(uint8_t protection) {
	if (protection)
		__HAL_RTC_WRITEPROTECTION_ENABLE(&hrtc);
	else
		__HAL_RTC_WRITEPROTECTION_DISABLE(&hrtc);

}


void Time_Get_Time(uint8_t *time) {
	HAL_RTC_GetTime( &hrtc, &rtc_time, RTC_FORMAT_BIN );
	time[0] = rtc_time.Hours;
	time[1] = rtc_time.Minutes;
	time[2] = rtc_time.Seconds;
}




