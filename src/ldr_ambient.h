/*
 * Alchemorium - ESP32-based Environmental Monitoring and Research Station
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 */

#include "serial_debug.h"
#include "lcd_display.h"

#ifndef LDR_AMBIENT_H
#define LDR_AMBIENT_H

#define LDR_PIN 34    // analog pin to the module
#define LDR_THRESHOLD 2800 // Darkness threshold. Analog value from LDR module. Higher = Darker
#define CONFIDENCE 4  // Darkness Confidence: Confirmed dark after this many threshold readings

static int lastLightLevel = 0;

bool initAmbientLightSensor();
void evaluateLightConditions();
int getLastLightLevel();

#endif