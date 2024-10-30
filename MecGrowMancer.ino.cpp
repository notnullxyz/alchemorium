#include <Arduino.h>

// Custom module headers
#include "src/lcd_display.h"
#include "src/bmp280_sensor.h"
#include "src/idle_mode.h"
#include "src/serial_debug.h"
#include "src/scheduler.h"

// Other necessary libraries

// Global variables (if any)

// Function prototypes (if any)

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
  setDebugLevel(DEBUG_VERBOSE);
}

void loop() {
  updateIdleDisplay();
  delay(3000);
}