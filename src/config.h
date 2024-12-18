// config.h
#ifndef CONFIG_H
#define CONFIG_H
#include <pgmspace.h>

#define DEVICE_NAME "Alchemorium"  // Global device name
#define VERSION "v1.4"             // global device version

/*
  Configuration Constants : Stored in PROGMEM
  Delcare/Define new config constants here AND amend config.cpp

  A note on mem/buffer:
  I hardcoded a 24 byte static buffer into config.cpp.
  If you're going to be using super long strings, change it to 32bytes or whatever.
*/

/**
 * I2C Custom Pins
 */
#define SDA_PIN 32  // Non Default SDA pin
#define SCL_PIN 33  // Non Default SCL pin

// WiFi Network
const char WIFI_SSID[] PROGMEM = "woodhouse";
const char WIFI_PASSWORD[] PROGMEM = "zingerwings";
const unsigned long WIFI_TIMEOUT = 20000;      // Timeout for a wifi connection in millis
const unsigned long WIFI_RETRY_DELAY = 60000;  // Retry wifi delay in millis

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
#define LCD_UPDATE_INTERVAL 1000  // LCD updates/redraws. Generally 1s is good (clock looks good, and data is fresh)
#define LDR_BACKLIGHT_CHECK 3000  // how often to check for darkness, so we can turn off the backlight

/**
 * Web Server Stuff (websrv)
 */

#define HTTPD_PORT 80  // the port number for web server request. Default 80

#endif
