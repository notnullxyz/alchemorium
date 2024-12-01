/*
 * Alchemorium - ESP32-based Environmental Monitoring and Research Station
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 */

#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>
#include <WiFi.h>
#include "rtc_module.h"
#include "config.h"

const unsigned long WIFI_TIMEOUT = 20000;      // Timeout for a wifi connection in millis
const unsigned long WIFI_RETRY_DELAY = 60000;  // Retry wifi delay in millis

// Globals to keep track of NTP timings - closely tied together.
extern unsigned long lastNTPTime;
const unsigned long NTP_SYNC_INTERVAL =
    24 * 60 * 60 * 1000UL;  // NTP sync interval. As little as possible, as much as needed.

bool initWiFi();
bool connectWiFi();
void checkWiFiConnection();
bool isWiFiConnected();
bool setWiFiCredentials();

// not used, unless enabled in wifi_manager.cpp:
// void setWiFiCredentials(const char* ssid, const char* password);
// void inputWiFiCredentialsSerial();

#endif
