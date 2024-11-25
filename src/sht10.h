/*
 * Alchemorium - ESP32-based Environmental Monitoring and Research Station
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 */

#ifndef SHT10_H
#define SHT10_H

#include <Arduino.h>

// Define SHT10 pins
#define SHT10_DATA_PIN 19 // Adjust as needed
#define SHT10_CLOCK_PIN 23 // Adjust as needed

#define SHT10_UPDATE_INTERVAL 30

#define CLOCK_TIMING_DELAY_uS 25

bool initSHT10();
float readSHT10Temperature();
float readSHT10Humidity();

#endif
