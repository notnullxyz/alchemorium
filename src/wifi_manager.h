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
