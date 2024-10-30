#include <Arduino.h>

// Custom module headers
#include "src/lcd_display.h"
#include "src/bmp280_sensor.h"

#include "src/serial_debug.h"
#include "src/scheduler.h"

// Cooperative multitasking with configurable CPU yield
const uint8_t CPU_THROTTLE_PERCENTAGE = 10;  // 10% throttle
const uint32_t LOOP_DELAY_MS = (100 * CPU_THROTTLE_PERCENTAGE) / 100;

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
  }

  // Add tasks to the scheduler
  scheduler.addTask(updateLCDDisplay, 1000);  // run lcd upd every sec, even if sensor upds are less frequent

  // And more here...
  // scheduler.addTask(updateWebServer, 100);  // Update web server every 100ms
  // scheduler.addTask(controlRelays, 60000);  // Control relays every minute

  setDebugLevel(DEBUG_VERBOSE);
}

void loop() {
  scheduler.run();
  delay(LOOP_DELAY_MS);
}
