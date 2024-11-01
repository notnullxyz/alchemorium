/*
 * MecGrowMancer - ESP32-based Homestead/Farm/Garden/Home/Garage Manager
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 */

#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>
#include <WiFi.h>

bool initWiFi();
bool connectWiFi();
void checkWiFiConnection();
bool isWiFiConnected();
void setWiFiCredentials();

// not used, unless enabled in wifi_manager.cpp:
//void setWiFiCredentials(const char* ssid, const char* password);
//void inputWiFiCredentialsSerial();

#endif
