#include <Arduino.h>

// Custom module headers
#include "src/lcd_display.h"
#include "src/bmp280_sensor.h"
#include "src/idle_mode.h"
#include "src/serial_debug.h"
#include "src/scheduler.h"

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
    scheduler.addTask(updateIdleDisplay, 5000);  // Update idle display every 5 seconds

    // Add more tasks here as you develop new features
    // For example:
    // scheduler.addTask(checkSensors, 1000);  // Check sensors every second
    // scheduler.addTask(updateWebServer, 100);  // Update web server every 100ms
    // scheduler.addTask(controlRelays, 60000);  // Control relays every minute

    setDebugLevel(DEBUG_VERBOSE);

    // Any other initializations from your original setup...
}

void loop() {
    scheduler.run();
    // Your loop can now be empty or contain only non-blocking code
    // If you had any other non-blocking code in your original loop, you can keep it here
}