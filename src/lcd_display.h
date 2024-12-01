/*
 * Alchemorium - ESP32-based Environmental Monitoring and Research Station
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 */

#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#include "config.h"
#include <LiquidCrystal_I2C.h>
#include "serial_debug.h"
#include "lcd_custom_chars.h"
#include "bmp280_sensor.h"
#include <time.h>
#include "rtc_module.h"

#define LCD_COLUMNS 16  // we use a 1602, 16 chars per line (2 lines)
#define LCD_ROWS 2
#define UPDATE_INTERVAL 3000  // ms interval for metrics rotation

#define SELF_TEST_FILL_AND_CLEAR_DELAY 22
#define SELF_TEST_HOLD_DELAY 1000

void initLCD();                                // initialise the LCD
void displayLine(int line, const char* text);  // Display 'text' on 'line' number
void clearLine(int line);                      // clears the lcd line number
void centerText(int line, const char* text);   // display centered text on 'line' number
void updateLCDDisplay();                       // update the display with the latest available data
void displayTemporaryMessage(const char* line1, const char* line2,
                             unsigned long duration);  // Temporary display line1+line2 for duration ms (use sparingly)
void toggleLCDBacklight(
    bool state);  // turn the backlight on or off by providing a boolean value (avoid rapid switching)

// Declare these as external functions
extern float readTemperature();
extern float readPressure();

#endif
