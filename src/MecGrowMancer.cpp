/*
 * MecGrowMancer - ESP32-based Homestead/Farm/Garden/Home/Garage Manager
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 */

// converting from ino to cpp - need this. pio says so.
#include <Arduino.h>

// Custom module headers
#include "src/lcd_display.h"
#include "src/bmp280_sensor.h"
#include "src/rtc_module.h"
#include "src/serial_debug.h"
#include "src/scheduler.h"
#include "src/wifi_manager.h"

// Cooperative multitasking with configurable CPU yield - keeping this here for now.
const uint8_t CPU_THROTTLE_PERCENTAGE = 10;  // 10% throttle
const uint32_t LOOP_DELAY_MS = (100 * CPU_THROTTLE_PERCENTAGE) / 100;

const unsigned long LCD_UPDATE_INTERVAL = 1000;  // every second

void setup() {
  initDebug();
  initLCD();

  if (!initTempAndPressureSystem()) {
    debugPrintln("main: initTempAndPressureSystem() fail", DEBUG_ERROR);
    displayTemporaryMessage("Sensors Init", "Temp/Pres Fail", 1000);
  }

  // Initialise the wifi. See comments inside:
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

  // Initialise the real time clock.
  if (!initRTC()) {
    debugPrintln("main: initRTC() fail", DEBUG_ERROR);
    displayTemporaryMessage("RTC Init", "Failed", 1000);
  } else {
    syncRTCWithNTP();
    displayTemporaryMessage("RTC Init", "OK.", 1000);
  }

  // Add tasks to the scheduler
  scheduler.addTask(updateLCDDisplay, LCD_UPDATE_INTERVAL);
  scheduler.addTask(syncRTCWithNTP, NTP_SYNC_INTERVAL);
  scheduler.addTask(checkWiFiConnection, 60000);

  setDebugLevel(DEBUG_VERBOSE);
}


void loop() {
  scheduler.run();
  delay(LOOP_DELAY_MS);
}
