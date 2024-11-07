/*
 * MecGrowMancer - ESP32-based Homestead/Farm/Garden/Home/Garage Manager
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

void updateTemperatureAndPressure();


#endif  // SENSOR_DATA_H
