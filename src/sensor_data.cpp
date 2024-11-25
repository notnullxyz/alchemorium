/*
 * Alchemorium - ESP32-based Environmental Monitoring and Research Station
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 * 
 * This file deals with the updating (called from scheduler, usually) functions from inputs.
 * It stores all 'last read' sensor data in the SensorData structure, and encapsulates it here.
 */

#include "sensor_data.h"
#include "bmp280_sensor.h"
#include "sht10.h"

SensorData g_sensorData = {0.0f, 0.0f};  // init with defaults.

// Calls to the bmp280_sensor code.
void updateTemperatureAndPressure() {
  g_sensorData.temperature = readTemperature();
  g_sensorData.pressure = readPressure();
}

void updateSHT10SensorData() {
  g_sensorData.temperature2 = readSHT10Temperature();
  g_sensorData.humidity = readSHT10Humidity();
}
