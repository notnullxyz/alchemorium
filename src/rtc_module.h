#ifndef RTC_MODULE_H
#define RTC_MODULE_H

#include <RTClib.h>

extern RTC_DS3231 rtc;

bool initRTC();
DateTime getCurrentTime();
void setRTCTime(const DateTime& dt);

// placeholder. Will use ntp over wifi to synchronise time.
void syncRTCWithNTP();

#endif
