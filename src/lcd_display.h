/*
 * MecGrowMancer - ESP32-based Homestead/Farm/Garden/Home/Garage Manager
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 */

#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#include <LiquidCrystal_I2C.h>
#include "serial_debug.h"
#include "lcd_custom_chars.h"
#include "sensor_data.h"
#include <time.h>
#include "rtc_module.h"

#define DEVICE_NAME "MecGrowMancer"
#define VERSION "v1.1"
#define LCD_COLUMNS 16  // we use a 1602, 16 chars per line (2 lines)
#define LCD_ROWS 2
#define UPDATE_INTERVAL 5000  // ms interval for metrics rotation

void initLCD();
void displayLine(int line, const char* text);
void clearLine(int line);
void centerText(int line, const char* text);
void updateLCDDisplay();
void displayTemporaryMessage(const char* line1, const char* line2, unsigned long duration);

#endif