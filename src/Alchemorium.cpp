/*
 * Alchemorium - ESP32-based Environmental Monitoring and Research Station
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 */

#include "Alchemorium.h"

void setup() {
  initDebug();
  initLCD();

  // INIT - Temperature and Pressure
  if (!initTempAndPressureSystem()) {
    debugPrintln("main: initTempAndPressureSystem() fail", DEBUG_ERROR);
    displayTemporaryMessage("Sensors Init", "Temp/Pres Fail", 1000);
  }

  // INIT - WiFi
  if (!initWiFi()) {
    debugPrintln("main: initWiFi() fail", DEBUG_ERROR);
    displayTemporaryMessage("WiFi Init", "Failed", 1000);
  } else {
    // Update the LCD to show the connection status immediately
    displayTemporaryMessage("Connecting to", "WiFi...", 800);

    // Either we load from config.h or input by serial (for dev)... choose one of:
    if (setWiFiCredentials()) {  // Set creds from config.h
      if (connectWiFi()) {
        debugPrintln("main: connectWiFi success", DEBUG_INFO);
        displayTemporaryMessage("WiFi", "Connected", 700);
      } else {
        displayTemporaryMessage("WiFi", "Connect Failed", 1200);
      }
    } else {
      displayTemporaryMessage("WiFi", "No credentials in config", 1200);
    }
  }

  // INIT - RTC
  if (!initRTC()) {
    debugPrintln("main: initRTC() fail", DEBUG_ERROR);
    displayTemporaryMessage("RTC Init", "Failed", 1000);
  } else {
    syncRTCWithNTP();
    displayTemporaryMessage("RTC Init", "OK.", 1000);
  }

  /**
   * ******** SCHEDULER TASKS *****************************
   * Each task must be clearly named and timed (preferably with a descriptive conf/constant)
   */
  scheduler.addTask(updateLCDDisplay, LCD_UPDATE_INTERVAL);
  scheduler.addTask(syncRTCWithNTP, NTP_SYNC_INTERVAL);
  scheduler.addTask(checkWiFiConnection, WIFI_RETRY_DELAY);
  scheduler.addTask(updateTemperatureAndPressure, SENSOR_UPDATE_TMPPRES_INT);

  setDebugLevel(DEBUG_VERBOSE);
}


void loop() {
  scheduler.run();
  delay(LOOP_DELAY_MS);
}
