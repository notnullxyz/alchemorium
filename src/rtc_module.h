/*
 * Alchemorium - ESP32-based Environmental Monitoring and Research Station
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 */

#ifndef RTC_MODULE_H
#define RTC_MODULE_H

#include <ThreeWire.h>
#include <RtcDS1302.h>
#include <WiFi.h>
#include <Timezone.h>
#include "config.h"

extern RtcDS1302<ThreeWire> Rtc;

// RTC Pins - DS1302 in this case
const int DAT = 17;  // DAT (orig 26)
const int CLK = 16;  // CLK (orig 25)
const int RST = 5;   // RST (orig 27)

bool initRTC();
RtcDateTime getCurrentTime();
void setRTCTime(const RtcDateTime& dt);

// placeholder until we have wifi connectivity
void syncRTCWithNTP();

#endif
