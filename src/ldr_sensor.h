/*
 * MecGrowMancer - ESP32-based Homestead/Farm/Garden/Home/Garage Manager
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 */

#ifndef LDR_SENSOR_H
#define LDR_SENSOR_H

#include <Arduino.h>
#include "serial_debug.h"

#define LDR_PIN 33

// Filtering. See README.md
#define LDR_FILTER_ALPHA 0.1
#define MAX_CHANGE 100
#define DRASTIC_CHANGE_THRESHOLD 500

bool initLDR();
int16_t readLDRAnalog();
int16_t readLDRAnalogFiltered();

#endif