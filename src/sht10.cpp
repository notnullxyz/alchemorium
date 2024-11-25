/*
 * Alchemorium - ESP32-based Environmental Monitoring and Research Station
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 */

#include "sht10.h"

// Define SHT10 pins
#define SHT10_DATA_PIN 19 // Adjust as needed
#define SHT10_CLOCK_PIN 23 // Adjust as needed

// Create an instance of the SHT1x library
SHT1x sht1x(SHT10_DATA_PIN, SHT10_CLOCK_PIN);

/**
 * @brief Initializes the SHT10 sensor.
 * 
 * @return true if the sensor is initialized successfully, false otherwise.
 */
bool initSHT10() {
    // No explicit initialization needed with the library
    return true;
}

/**
 * @brief Reads the temperature from the SHT10 sensor.
 * 
 * @return Temperature in degrees Celsius, or NAN if an error occurs.
 */
float readSHT10Temperature() {
    float temperature = sht1x.readTemperatureC();
    if (temperature == 0) { // Assuming 0 is an error condition
        return NAN; // Or handle error as needed
    }
    return temperature;
}

/**
 * @brief Reads the humidity from the SHT10 sensor.
 * 
 * @return Relative humidity in percentage, or NAN if an error occurs.
 */
float readSHT10Humidity() {
    float humidity = sht1x.readHumidity();
    if (humidity == 0) { // Assuming 0 is an error condition
        return NAN; // Or handle error as needed
    }
    return humidity;
}
