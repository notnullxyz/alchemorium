
#include "bmp280_sensor.h"
#include "serial_debug.h"

Adafruit_BMP280 bmp;  // Declare the sensor object

bool initTempAndPressureSystem(void (*displayCallback)(const char*, const char*)) {
    debugPrintln("Initializing BMP280...", DEBUG_INFO);
    
    if (!bmp.begin(0x77, BMP280_CHIPID)) {
        debugPrintln("initTempAndPressureSystem(): Valid BMP280 Not Detected", DEBUG_ERROR);
        if (displayCallback) {
            displayCallback("BMP280 Init", "Failed!");
        }
        return false;
    }
    
    debugPrintln("initTempAndPressureSystem(): OK", DEBUG_INFO);

    // Default settings from datasheet
    bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,      // Operating Mode
                    Adafruit_BMP280::SAMPLING_X4,      // Temp. oversampling
                    Adafruit_BMP280::SAMPLING_X16,     // Pressure oversampling
                    Adafruit_BMP280::FILTER_X16,       // Filtering
                    Adafruit_BMP280::STANDBY_MS_500);  // Standby time

    debugPrintln("initTempAndPressureSystem(): BMP280 Init OK", DEBUG_VERBOSE);
   
    return true;
}

float readTemperature() {
    float temp = bmp.readTemperature();
    if (isnan(temp)) {
        debugPrintln("Failed to read temperature", DEBUG_ERROR);
        return -999.99; // an impossible value to indicate error
    }
    debugPrintf(DEBUG_VERBOSE, "Temperature: %.2f °C\n", temp);
    return temp;
}

float readPressure() {
    float pressure = bmp.readPressure() / 100.0F; // Convert Pa to hPa
    if (isnan(pressure)) {
        debugPrintln("Failed to read pressure", DEBUG_ERROR);
        return -999.99; // an impossible value to indicate error
    }
    debugPrintf(DEBUG_VERBOSE, "Pressure: %.2f hPa\n", pressure);
    return pressure;
}
