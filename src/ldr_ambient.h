/*
 * Alchemorium - ESP32-based Environmental Monitoring and Research Station
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 */

#include "serial_debug.h"
#include "lcd_display.h"

#ifndef LDR_AMBIENT_H
#define LDR_AMBIENT_H

#define LDR_PIN 34    // analog
#define LDR_THRESHOLD 2800 // what is darkness????
#define CONFIDENCE 4  // It's confirmed to be dark after this many readings

bool initAmbientLightSensor();
void measureLightForLCD();

#endif