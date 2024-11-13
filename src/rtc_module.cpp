/*
 * Alchemorium - ESP32-based Environmental Monitoring and Research Station
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 */

#include "rtc_module.h"
#include "serial_debug.h"
#include "lcd_display.h"

// RTC Pins - DS1302 in this case
const int DAT = 26;  // DAT
const int CLK = 25;  // CLK
const int RST = 27;  // RST

// default South Africa Standard Time (SAST) timezone rules
TimeChangeRule saTime = {"SAST", Last, Sun, Mar, 2, 120};  // UTC +2 hours, no DST
Timezone myTZ(saTime, saTime);  // same, we don't have DST here

ThreeWire myWire(DAT, CLK, RST);
RtcDS1302<ThreeWire> Rtc(myWire);
bool initRTC() {

  Rtc.Begin();
  if (!Rtc.IsDateTimeValid()) {
    debugPrintln("RTC: lost confidence in DateTime", DEBUG_WARNING);
    // set a default, compile time.
    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    Rtc.SetDateTime(compiled);
  }
  if (!Rtc.GetIsRunning()) {
    debugPrintln("RTC: Not running. Starting now", DEBUG_INFO);
    Rtc.SetIsRunning(true);
  }
  return true;
}

RtcDateTime getCurrentTime() {
  return Rtc.GetDateTime();
}

void setRTCTime(const RtcDateTime& dt) {
  Rtc.SetDateTime(dt);
}

// When connected to wifi, we can correct drift from network time
void syncRTCWithNTP() {
  debugPrintln("RTC: Syncing RTC with NTP", DEBUG_INFO);

  if (WiFi.status() != WL_CONNECTED) {
    displayTemporaryMessage("NTP: Sync Fail", "No WiFi", 3000);
    debugPrintln("RTC: no WiFi = no NTP sync.", DEBUG_ERROR);
    return;
  }

  const char* ntp_server1 = getConfig("NTP_SERVER1");
  const char* ntp_server2 = getConfig("NTP_SERVER2");
  if (ntp_server1 && ntp_server2) {
    configTime(0, 0, ntp_server1, ntp_server2);
    debugPrintln("RTC: Using custom NTP servers from config", DEBUG_INFO);
  } else {
    configTime(0, 0, "pool.ntp.org", "time.nist.gov");
    debugPrintln("RTC: Using default NTP servers in rtc_module", DEBUG_INFO);
  }

  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    displayTemporaryMessage("NTP: Sync Fail", "From NTP Server", 3000);
    debugPrintln("RTC: Failed to obtain time from NTP", DEBUG_ERROR);
    return;
  }

  time(&now);
  time_t local = myTZ.toLocal(now);

  RtcDateTime localTime = RtcDateTime(
    year(local),
    month(local),
    day(local),
    hour(local),
    minute(local),
    second(local));

  setRTCTime(localTime);
  debugPrintln("RTC: NTP sync successful", DEBUG_INFO);
  displayTemporaryMessage("NTP: Sync OK", "Time Adjusted", 2000);
}
