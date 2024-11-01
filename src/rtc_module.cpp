#include "rtc_module.h"
#include "serial_debug.h"
#include "lcd_display.h"

const int DAT = 26;  // DAT
const int CLK = 25;  // CLK
const int RST = 27;  // RST

ThreeWire myWire(DAT, CLK, RST);
RtcDS1302<ThreeWire> Rtc(myWire);
bool initRTC() {

  Rtc.Begin();
  if (!Rtc.IsDateTimeValid()) {
    debugPrintln("RTC lost confidence in the DateTime!", DEBUG_WARNING);
    // set a default, compile time.
    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    Rtc.SetDateTime(compiled);
  }
  if (!Rtc.GetIsRunning()) {
    debugPrintln("RTC not running, so starting now", DEBUG_INFO);
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
  debugPrintln("Syncing RTC with NTP...", DEBUG_INFO);

  if (WiFi.status() != WL_CONNECTED) {
    displayTemporaryMessage("NTP: Sync Fail", "No WiFi", 3000);
      debugPrintln("WiFi not connected. Cannot sync with NTP.", DEBUG_ERROR);
    return;
  }

  // pre-processor condition: if ntp servers defined in config.h... else defaults
  #if defined(NTP_SERVER1) && defined(NTP_SERVER2)
    configTime(0, 0, NTP_SERVER1, NTP_SERVER2);
    debugPrintln("Using custom NTP servers from config", DEBUG_INFO);
  #else
    configTime(0, 0, "pool.ntp.org", "time.nist.gov");
    debugPrintln("Using default NTP servers in rtc_module", DEBUG_INFO);
  #endif

  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    displayTemporaryMessage("NTP: Sync Fail", "From NTP Server", 3000);
      debugPrintln("Failed to obtain time from NTP", DEBUG_ERROR);
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
  debugPrintln("RTC synced with NTP successfully", DEBUG_INFO);
  displayTemporaryMessage("NTP: Sync OK", "Time Adjusted", 2000);
}
