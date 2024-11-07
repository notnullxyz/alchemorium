// config.h
#ifndef CONFIG_H
#define CONFIG_H
#include <pgmspace.h>

/*
  Configuration Constants : Stored in PROGMEM
  Delcare/Define new config constants here AND amend config.cpp

  A note on mem/buffer:
  I hardcoded a 24 byte static buffer into config.cpp.
  If you're going to be using super long strings, change it to 32bytes or whatever.
*/

// WiFi Network
const char WIFI_SSID[] PROGMEM = "woodhouse";
const char WIFI_PASSWORD[] PROGMEM = "zingerwings";

// NTP Servers
const char NTP_SERVER1[] PROGMEM = "0.za.pool.ntp.org";
const char NTP_SERVER2[] PROGMEM = "1.za.pool.ntp.org";

// System Timezone
const char TZ_STRING[] PROGMEM = "SAST-2";

// getter for configuration constants
char* getConfig(const char* key);

/**
 * LDR - Light Level Measurement Section
 */
#define LDR_INTERVAL 5000               // how often in ms, to do light measurements
// LDR - Filtering. 
#define LDR_FILTER_ALPHA 0.2            // how quickly to respond to change. Lower = smoother, but slower
#define MAX_CHANGE 100                  // prevent spikes by capping maximum change (in filtered values) between readings
#define DRASTIC_CHANGE_THRESHOLD 500    // what constitutes a drastic change? If raw vs filtered values exceed this = it's considered significant

#endif
