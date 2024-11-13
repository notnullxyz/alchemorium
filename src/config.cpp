/*
 * Alchemorium - ESP32-based Environmental Monitoring and Research Station
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 */

#include "config.h"
#include <string.h>

// Retrieve the configuration value from config.h
#include "config.h"
#include <string.h>
#include <stdlib.h>

// Retrieve the configuration value from config.h
// Returns a dynamically alloc'd string - free!
char* getConfig(const char* key) {
  const char* value = NULL;

  if (strcmp(key, "WIFI_SSID") == 0) {
    value = WIFI_SSID;
  } else if (strcmp(key, "WIFI_PASSWORD") == 0) {
    value = WIFI_PASSWORD;
  } else if (strcmp(key, "NTP_SERVER1") == 0) {
    value = NTP_SERVER1;
  } else if (strcmp(key, "NTP_SERVER2") == 0) {
    value = NTP_SERVER2;
  } else if (strcmp(key, "TZ_STRING") == 0) {
    value = TZ_STRING;
  }

  if (value != NULL) {
    char* result = strdup(value);
    if (result == NULL) {
      return NULL;
    }
    return result;
  }

  return NULL;
}
