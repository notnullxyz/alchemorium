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
 * LCD Section
 */
#define LCD_UPDATE_INTERVAL 1000   // LCD updates/redraws. Generally 1s is good (clock looks good, and data is fresh)
#define LDR_BACKLIGHT_CHECK 3000  // how often to check for darkness, so we can turn off the backlight

#endif
