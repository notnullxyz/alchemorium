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

  if (!initRTC()) {
    debugPrintln("Failed to initialize RTC", DEBUG_ERROR);
  }

  if (!initTempAndPressureSystem(displayOnLCD)) {
    debugPrintln("Failed to initialize BMP280", DEBUG_ERROR);
  }

  // Initialise the wifi. See comments inside:
  if (!initWiFi()) {
    debugPrintln("Failed to initialize WiFi", DEBUG_ERROR);
    displayTemporaryMessage("WiFi Init", "Failed", 2000);
  } else {
    displayTemporaryMessage("Connecting", "to WiFi...", 1000);
    // Either we load from config.h or input by serial (for dev)... choose one of:
    setWiFiCredentials();  // Load from config.h
    // inputWiFiCredentialsSerial(); // Prompt on Serial interface
    if (connectWiFi()) {
      debugPrintln("WiFi connected successfully", DEBUG_INFO);
      displayTemporaryMessage("WiFi", "Connected", 2000);
    } else {
      displayTemporaryMessage("WiFi", "Connect Failed", 2000);
    }
  }

  // Add tasks to the scheduler
  scheduler.addTask(updateLCDDisplay, LCD_UPDATE_INTERVAL);  // run lcd upd every...
  scheduler.addTask(syncRTCWithNTP, NTP_SYNC_INTERVAL);      // update the RTC via NTP every...
  scheduler.addTask(checkWiFiConnection, 60000);          // checl wifi every minute

  // And more here...
  // scheduler.addTask(updateWebServer, 100);  // Update web server every 100ms
  // scheduler.addTask(controlRelays, 60000);  // Control relays every minute

  setDebugLevel(DEBUG_VERBOSE);
}

void loop() {
  scheduler.run();
  delay(LOOP_DELAY_MS);
}
