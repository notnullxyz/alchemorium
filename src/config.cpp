/*
 * MecGrowMancer - ESP32-based Homestead/Farm/Garden/Home/Garage Manager
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 */

#include "config.h"
#include <string.h>

static char buffer[24];

// Retrieve the configuration value from config.h
const char* getConfig(const char* key) {
    if (strcmp(key, "WIFI_SSID") == 0) {
        strcpy_P(buffer, WIFI_SSID);
    } else if (strcmp(key, "WIFI_PASSWORD") == 0) {
        strcpy_P(buffer, WIFI_PASSWORD);
    } else if (strcmp(key, "NTP_SERVER1") == 0) {
        strcpy_P(buffer, NTP_SERVER1);
    } else if (strcmp(key, "NTP_SERVER2") == 0) {
        strcpy_P(buffer, NTP_SERVER2);
    } else if (strcmp(key, "TZ_STRING") == 0) {
        strcpy_P(buffer, TZ_STRING);
    } else {
        return NULL;
    }
    return buffer;
}
