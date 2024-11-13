/*
 * Alchemorium - ESP32-based Environmental Monitoring and Research Station
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 */

#ifndef BMP280_SENSOR_H
#define BMP280_SENSOR_H

#include <Adafruit_BMP280.h>

extern Adafruit_BMP280 bmp;
bool initTempAndPressureSystem();

bool initTempAndPressureSystem();
float readTemperature();
float readPressure();

#endif
