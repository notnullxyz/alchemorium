/*
 * Alchemorium - ESP32-based Environmental Monitoring and Research Station
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 */

#ifndef SHT10_H
#define SHT10_H

#define I2C_SHT10_ADDRESS 0x00

bool initSHT10();
float readSHT10Temperature();
float readSHT10Humidity();

#endif