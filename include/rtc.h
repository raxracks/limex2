#ifndef RTC_H
#define RTC_H

#include <stdint.h>

int rtc_year();
int rtc_month();
int rtc_day();
int rtc_hour();
int rtc_minute();
int rtc_second();
void rtc_print();

#endif