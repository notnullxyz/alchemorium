/*
 * Alchemorium - ESP32-based Environmental Monitoring and Research Station
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 */

#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

struct SensorData {
    float temperature;
    float pressure;
};

extern SensorData g_sensorData;

void updateTemperatureAndPressure();  // BMP280

#endif  // SENSOR_DATA_H
