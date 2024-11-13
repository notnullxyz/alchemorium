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

  // no wifi connected? No time for you. S7/E6
  if (WiFi.status() != WL_CONNECTED) {
    displayTemporaryMessage("NTP: Sync Fail", "No WiFi", 3000);
    debugPrintln("RTC: no WiFi = no NTP sync.", DEBUG_ERROR);
    return;
  }

  // Set timezone (standard tz string)
  const char* timezone = getConfig("TZ_STRING");
  if (timezone) {
    debugPrintln("RTC: Found TZ_STRING in config, using that");
    setenv("TZ", timezone, 1);
    tzset();
  } else {
    debugPrintln("RTC: TZ_STRING not found. Not doing setenv(TZ...");
  }

  // IMPORTANT: please see README about NTP servers. Don't use anything you can put your paws on.
  const char* ntp_server1 = getConfig("NTP_SERVER1");
  const char* ntp_server2 = getConfig("NTP_SERVER2");
  if (ntp_server1 && ntp_server2) {
    configTime(0, 0, ntp_server1, ntp_server2);
    debugPrintln("RTC: Using custom NTP servers from config", DEBUG_INFO);
  } else {
    configTime(0, 0, "pool.ntp.org", "time.nist.gov");
    debugPrintln("RTC: Using hardcoded default NTP servers in rtc_module", DEBUG_INFO);
  }

  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    displayTemporaryMessage("NTP: Sync Fail", "From NTP Server", 3000);
    debugPrintln("RTC: Failed to obtain time from NTP", DEBUG_ERROR);
    return;
  }

  time(&now);

  RtcDateTime ntpTime = RtcDateTime(
    timeinfo.tm_year + 1900,
    timeinfo.tm_mon + 1,
    timeinfo.tm_mday,
    timeinfo.tm_hour,
    timeinfo.tm_min,
    timeinfo.tm_sec);

  setRTCTime(ntpTime);
  debugPrintln("RTC: NTP sync successfull", DEBUG_INFO);
  displayTemporaryMessage("NTP: Sync OK", "Time Adjusted", 2000);
}
