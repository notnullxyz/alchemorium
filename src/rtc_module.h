/*
 * MecGrowMancer - ESP32-based Homestead/Farm/Garden/Home/Garage Manager
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 */

#ifndef RTC_MODULE_H
#define RTC_MODULE_H

#include <ThreeWire.h>
#include <RtcDS1302.h>
#include <WiFi.h>
#include "config.h"

extern RtcDS1302<ThreeWire> Rtc;

bool initRTC();
RtcDateTime getCurrentTime();
void setRTCTime(const RtcDateTime& dt);

// placeholder until we have wifi connectivity
void syncRTCWithNTP();

#endif