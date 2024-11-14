/*
 * MecGrowMancer - ESP32-based Homestead/Farm/Garden/Home/Garage Manager
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 */

#include "ldr_sensor.h"
#include <math.h>

bool initLDR() {
    debugPrintf(DEBUG_VERBOSE, "ldr_sensor: init on pin %d\n", LDR_PIN);

    pinMode(LDR_PIN, INPUT);
    analogReadResolution(12);       // Set to 12-bit resolution
    analogSetAttenuation(ADC_11db); // Set attenuation to extend range to 3.3V

    // Measure an initial value, to determine if the sensor is actually functional.
    int16_t initialValue = readLDRAnalog();
    if (initialValue == -1) {
        debugPrintln("ldr_sensor: failed to read initial value", DEBUG_ERROR);
        return false;
    }

    debugPrintln("ldr_sensor: initialization successful", DEBUG_INFO);
    return true;
}

/*
  Plain old analog read. 
  For filtering @see readLDRAnalogFiltered()
  @param invert bool LDR modules invert, some don't. False to not invert.
 */
int16_t readLDRAnalog(bool invert) {
    int16_t rawValue = analogRead(LDR_PIN);
    debugPrintf(DEBUG_WARNING, "ldr_sensor: read ldr analog: %d\n", rawValue);

    // Safe check for analog reading
    if (rawValue < 0 || rawValue > 4095) {
        debugPrintf(DEBUG_WARNING, "ldr_sensor: values out of bounds: %d\n", rawValue);
        return -1;
    }

    // Adjust the value based on the invert parameter
    if (invert) {
        debugPrintf(DEBUG_INFO, "ldr_sensor: using inverted value: %d", (4095 - rawValue));
        return 4095 - rawValue;  // Invert the value if specified
    } else {
        return rawValue;  // Return the raw value if no inversion is needed
    }
}

/*
  Return an EMA (exponential moving average) filtered reading from the LDR.
  @param invert bool LDR modules invert, some don't. False to NOT invert.
 */
int16_t readLDRAnalogFiltered(bool invert) {
    static float filteredValue = -1;  // Init to a negative value indicating no initial reading
    int16_t rawValue = readLDRAnalog(invert);
    debugPrintf(DEBUG_VERBOSE, "ldr_sensor: filtered: raw value = %d\n", rawValue);
    if (rawValue == -1) {
        return rawValue;    // return invalid if reading was invalid
    }

    if (filteredValue < 0) {
        filteredValue = rawValue;   // the first valid reading
    } else {
        // Apply EMA filter
        filteredValue = (LDR_FILTER_ALPHA * rawValue) + ((1 - LDR_FILTER_ALPHA) * filteredValue);
    }

    return static_cast<int16_t>(round(filteredValue));
}

/**
 * Lux as a unit.
 * To use this, we need to determine sensor type/design/indirect/direct
 * But more important, calibrating with a known lux meter, to set LDR_TO_LUX_SCALE and LDR_TO_LUX_OFFSET
 * @see ldr_sensor.h
 */

// Example: Calculate these based on actual calibration data
#define LDR_TO_LUX_SCALE 0.1  // Example scale factor
#define LDR_TO_LUX_OFFSET 0.0 // Example offset

float convertLDRToLux(float filteredValue) {
    return (filteredValue * LDR_TO_LUX_SCALE) + LDR_TO_LUX_OFFSET;
}

/*
  Get the filtered analog values, but converted to Lux.
  @param invert bool LDR modules invert, some don't. False to NOT invert.
*/
int16_t readLDRFilteredLux(bool invert) {
    int16_t filteredValue = readLDRAnalogFiltered(invert); // Pass invert parameter
    if (filteredValue == -1) {
        return -1;
    }
    return static_cast<int16_t>(round(convertLDRToLux(filteredValue)));
}
