#ifndef RTC_MODULE_H
#define RTC_MODULE_H

#include <ThreeWire.h>
#include <RtcDS1302.h>

extern RtcDS1302<ThreeWire> Rtc;

bool initRTC();
RtcDateTime getCurrentTime();
void setRTCTime(const RtcDateTime& dt);

// placeholder until we have wifi connectivity
void syncRTCWithNTP();

#endif