/*
 * Alchemorium - ESP32-based Environmental Monitoring and Research Station
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 */

#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#define DEVICE_NAME "Alchemorium"
#define VERSION "v1.2"
#define LCD_COLUMNS 16  // we use a 1602, 16 chars per line (2 lines)
#define LCD_ROWS 2
#define UPDATE_INTERVAL 3000  // ms interval for metrics rotation

#define SELF_TEST_FILL_AND_CLEAR_DELAY 22
#define SELF_TEST_HOLD_DELAY 1000

void initLCD();
void displayLine(int line, const char* text);
void clearLine(int line);
void centerText(int line, const char* text);
void updateLCDDisplay();
void displayTemporaryMessage(const char* line1, const char* line2, unsigned long duration);
void toggleLCDBacklight();

// Declare these as external functions
extern float readTemperature();
extern float readPressure();

#endif
