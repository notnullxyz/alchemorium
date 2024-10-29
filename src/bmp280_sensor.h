
#ifndef BMP280_SENSOR_H
#define BMP280_SENSOR_H

#include <Adafruit_BMP280.h>

extern Adafruit_BMP280 bmp;
bool initTempAndPressureSystem(void (*displayCallback)(const char*, const char*) = nullptr);

bool initTempAndPressureSystem();
float readTemperature();
float readPressure();

#endif