/*
 * MecGrowMancer - ESP32-based Homestead/Farm/Garden/Home/Garage Manager
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 */

#ifndef BMP280_SENSOR_H
#define BMP280_SENSOR_H

#include <Adafruit_BMP280.h>

extern Adafruit_BMP280 bmp;
bool initTempAndPressureSystem(void (*displayCallback)(const char*, const char*) = nullptr);

bool initTempAndPressureSystem();
float readTemperature();
float readPressure();

#endif