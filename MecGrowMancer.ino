/*
 * MecGrowMancer - ESP32-based Homestead/Farm/Garden/Home/Garage Manager
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 */

#include <Arduino.h>

// Custom module headers
#include "src/lcd_display.h"
#include "src/bmp280_sensor.h"
#include "src/rtc_module.h"
#include "src/serial_debug.h"
#include "src/scheduler.h"
#include "src/wifi_manager.h"

// Cooperative multitasking with configurable CPU yield
const uint8_t CPU_THROTTLE_PERCENTAGE = 10;  // 10% throttle
const uint32_t LOOP_DELAY_MS = (100 * CPU_THROTTLE_PERCENTAGE) / 100;

// NTP Synchronise RTP Interval
const unsigned long NTP_SYNC_INTERVAL = 24 * 60 * 60 * 1000UL;  // every 24 hours (how bad can it drift?)

const unsigned long LCD_UPDATE_INTERVAL = 1000;  // every second

void setup() {
  initDebug();
  initLCD();

  // Lambda function to display on LCD
  auto displayOnLCD = [](const char* line1, const char* line2) {
    displayLine(0, line1);
    displayLine(1, line2);
    delay(2000);  // Show message for 2 seconds
  };

  if (!initTempAndPressureSystem(displayOnLCD)) {
    debugPrintln("Failed to initialize BMP280", DEBUG_ERROR);
    displayTemporaryMessage("Sensors Init", "Temp/Pres Fail", 1500);
  }

  // Initialise the wifi. See comments inside:
  if (!initWiFi()) {
    debugPrintln("Failed to initialize WiFi", DEBUG_ERROR);
    displayTemporaryMessage("WiFi Init", "Failed", 1000);
  } else {
    displayTemporaryMessage("Connecting", "to WiFi...", 1000);
    
    // Either we load from config.h or input by serial (for dev)... choose one of:
    if (setWiFiCredentials()) {  // Set creds from config.h
      // inputWiFiCredentialsSerial(); // Prompt on Serial interface
      
      if (connectWiFi()) {
        debugPrintln("WiFi connected successfully", DEBUG_INFO);
        displayTemporaryMessage("WiFi", "Connected", 700);
      } else {
        displayTemporaryMessage("WiFi", "Connect Failed", 1200);
      }
    } else {
      displayTemporaryMessage("WiFi", "No credentials in config", 1200);
    }
  }

  // Initialise the real time clock.
  // Doing this after wifi. If wifi available, we can do a bootup sync with NTP, too.
  if (!initRTC()) {
    debugPrintln("Failed to initialize RTC", DEBUG_ERROR);
    displayTemporaryMessage("RTC Init", "Failed", 1000);
  } else {
    syncRTCWithNTP();
    displayTemporaryMessage("RTC Init", "OK.", 1000);
  }

  // Add tasks to the scheduler
  scheduler.addTask(updateLCDDisplay, LCD_UPDATE_INTERVAL);  // run lcd upd every...
  scheduler.addTask(syncRTCWithNTP, NTP_SYNC_INTERVAL);      // update the RTC via NTP every...
  scheduler.addTask(checkWiFiConnection, 60000);             // checl wifi every minute

  // And more here...
  // scheduler.addTask(updateWebServer, 100);  // Update web server every 100ms
  // scheduler.addTask(controlRelays, 60000);  // Control relays every minute

  // This is... quite verbose... set to info or something else for deployed use.
  setDebugLevel(DEBUG_VERBOSE);
}

void loop() {
  scheduler.run();
  delay(LOOP_DELAY_MS);
}
