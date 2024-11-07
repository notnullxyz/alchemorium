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

/**
 * Calibrating for Lux.
 * LDR_TO_LUX_SCALE scales the ADC(lux meter) value to match the lux measurement(LDR). It represents the sensitivity of the LDR in lux per ADC unit.
 * LDR_TO_LUX_OFFSET is constant added to the scaled ADC value to align it with the actual lux measurement, accounting for baseline indiscrepancies.
 */
const float LDR_TO_LUX_SCALE = 0.1f;  // Scale Factor
const float LDR_TO_LUX_OFFSET = 0.0f; // Offset

bool initLDR();

int16_t readLDRAnalog(bool invert = true);
int16_t readLDRAnalogFiltered(bool invert = true);
int16_t readLDRFilteredLux(bool invert = true); // calibrate for lux - above LDR_TO_LUX_SCALE and LDR_TO_LUX_OFFSET

#endif