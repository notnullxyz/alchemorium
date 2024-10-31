#include "rtc_module.h"
#include "serial_debug.h"

RTC_DS3231 rtc;

bool initRTC() {
  if (!rtc.begin()) {
    debugPrintln("Couldn't find RTC", DEBUG_ERROR);
    return false;
  }
  if (rtc.lostPower()) {
    debugPrintln("RTC lost power, setting default time", DEBUG_WARNING);
    // set time somehow here.
  }
  return true;
}

DateTime getCurrentTime() {
  return rtc.now();
}

void setRTCTime(const DateTime& dt) {
  rtc.adjust(dt);
}

// use NTP to synchronise the real time clock.
void syncRTCWithNTP() {
  debugPrintln("NTP sync not implemented yet", DEBUG_INFO);
}
