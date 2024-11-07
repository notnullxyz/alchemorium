/*
 * MecGrowMancer - ESP32-based Homestead/Farm/Garden/Home/Garage Manager
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 */

#ifndef LDR_SENSOR_H
#define LDR_SENSOR_H

#include <Arduino.h>
#include "serial_debug.h"
#include "config.h"

#define LDR_PIN 33

bool initLDR();
int16_t readLDRAnalog();
int16_t readLDRAnalogFiltered();

#endif