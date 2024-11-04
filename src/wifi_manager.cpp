/*
 * MecGrowMancer - ESP32-based Homestead/Farm/Garden/Home/Garage Manager
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 */

#include "wifi_manager.h"
#include "serial_debug.h"
#include "config.h"

const unsigned long WIFI_TIMEOUT = 20000;      // 20 seconds timeout for connection
const unsigned long WIFI_RETRY_DELAY = 60000;  // 1 minute delay before retry

static char wifi_ssid[32] = "";
static char wifi_password[64] = "";

bool initWiFi() {
  WiFi.mode(WIFI_STA);
  return true;
}

bool connectWiFi() {
  if (strlen(wifi_ssid) == 0 || strlen(wifi_password) == 0) {
    debugPrintln("WiFi credentials not set", DEBUG_ERROR);
    return false;
  }

  debugPrintln("Connecting to WiFi...", DEBUG_INFO);
  WiFi.begin(wifi_ssid, wifi_password);

  unsigned long startAttemptTime = millis();

  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < WIFI_TIMEOUT) {
    delay(100);
  }

  if (WiFi.status() != WL_CONNECTED) {
    debugPrintln("WiFi connection failed", DEBUG_ERROR);
    return false;
  }

  debugPrintln("WiFi connected", DEBUG_INFO);
  debugPrintln(WiFi.localIP().toString().c_str(), DEBUG_INFO);
  return true;
}

void checkWiFiConnection() {
  if (WiFi.status() != WL_CONNECTED) {
    debugPrintln("WiFi connection lost, reconnecting...", DEBUG_WARNING);
    WiFi.disconnect();
    connectWiFi();
  }
}

bool isWiFiConnected() {
  return WiFi.status() == WL_CONNECTED;
}

// Set the Wifi Creds from the values in config.h
bool setWiFiCredentials() {
  char* ssid = getConfig("WIFI_SSID");
  char* password = getConfig("WIFI_PASSWORD");

  if (ssid && password) {
    strncpy(wifi_ssid, ssid, sizeof(wifi_ssid) - 1);
    wifi_ssid[sizeof(wifi_ssid) - 1] = '\0';  // Ensure null-termination

    strncpy(wifi_password, password, sizeof(wifi_password) - 1);
    wifi_password[sizeof(wifi_password) - 1] = '\0';  // Ensure null-termination

    // free up the dyn alloc'd string from getConfig()
    free(ssid);
    free(password);
    debugPrintln("WiFi credentials set from config", DEBUG_INFO);
    return true;
  } else {
    debugPrintln("WiFi credentials not found in config", DEBUG_ERROR);
    wifi_ssid[0] = '\0';
    wifi_password[0] = '\0';
    return false;
  }
}


// This version of setWifiCredentials() is for calling from inputWifiCredentialsSerial()
/*
void setWiFiCredentials(const char* ssid, const char* password) {
  strncpy(wifi_ssid, ssid, sizeof(wifi_ssid));
  strncpy(wifi_password, password, sizeof(wifi_password));
}
*/

// Prompt on the Serial console for wifi credentials. Useful for dev only. Leaving this for convenience.
/*
void inputWiFiCredentialsSerial() {
  Serial.println("WiFi SSID:");
  while (!Serial.available()) {}
  String ssid = Serial.readStringUntil('\n');
  ssid.trim();
  
  Serial.println("WiFi Password:");
  while (!Serial.available()) {}
  String password = Serial.readStringUntil('\n');
  password.trim();
  
  setWiFiCredentials(ssid.c_str(), password.c_str());
}
*/
