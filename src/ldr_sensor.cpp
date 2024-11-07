/*
 * MecGrowMancer - ESP32-based Homestead/Farm/Garden/Home/Garage Manager
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 */
#include "ldr_sensor.h"
#include <math.h>

bool initLDR() {
    String debugMsg = "ldr_sensor: init on pin " + String(LDR_PIN);
    debugPrintln(debugMsg.c_str(), DEBUG_VERBOSE);

    pinMode(LDR_PIN, INPUT);

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

  // Safe check for analog reading
  if (rawValue < 0 || rawValue > 4095) {
    debugPrintln("ldr_sensor: values out of bounds");
    return -1;
  }

  // Adjust the value based on the invert parameter
  if (invert) {
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

// Simple linear conversion; usable only if calibrated
float convertLDRToLux(float filteredValue) {
  return (filteredValue * LDR_TO_LUX_SCALE) + LDR_TO_LUX_OFFSET;
}

/*
  Get the filtered analog values, but converted to Lux.
  @param invert bool LDR modules invert, some don't. False to NOT invert.
*/
int16_t readLDRFilteredLux(bool invert) {
  int16_t filteredValue = readLDRAnalogFiltered();
  if (filteredValue == -1) {
    return -1;
  }
  return static_cast<int16_t>(round(convertLDRToLux(filteredValue)));
}
