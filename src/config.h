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

// getter for configuration constants ^
char* getConfig(const char* key);

/**
 * LDR - Light Level Measurement Section
 */
#define LDR_FILTER_ALPHA 0.5f  // Smoothing factor, between 0 and 1 (higher = less smoothing, faster)
#define SENSOR_UPDATE_LDR_INT 3000      // take light readings every x seconds.

/**
 * LCD Section
 */
#define LCD_UPDATE_INTERVAL 1000   // LCD updates/redraws. Generally 1s is good (clock looks good, and data is fresh)

/**
 * Temperature and Pressure Section
 */
#define SENSOR_UPDATE_TMPPRES_INT 10000  // update interval for temperature and pressure sensors. Use discretion.

#endif
