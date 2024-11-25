/*
 * Alchemorium - ESP32-based Environmental Monitoring and Research Station
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 */

#ifndef SHT10_H
#define SHT10_H

#include <Arduino.h>
#include <SHT1x-ESP.h>

#define SHT10_UPDATE_INTERVAL 15

bool initSHT10();
float readSHT10Temperature();
float readSHT10Humidity();

#endif
