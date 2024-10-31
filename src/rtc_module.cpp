#include "rtc_module.h"
#include "serial_debug.h"

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

// TODO when we have wifi  connectivity
void syncRTCWithNTP() {
  debugPrintln("NTP sync not implemented yet", DEBUG_INFO);
}