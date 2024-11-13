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

// Globals to keep track of NTP timings - closely tied together.
extern unsigned long lastNTPTime;
const unsigned long NTP_SYNC_INTERVAL = 24 * 60 * 60 * 1000UL; // 24hrs

bool initWiFi();
bool connectWiFi();
void checkWiFiConnection();
bool isWiFiConnected();
bool setWiFiCredentials();

// not used, unless enabled in wifi_manager.cpp:
//void setWiFiCredentials(const char* ssid, const char* password);
//void inputWiFiCredentialsSerial();

#endif
