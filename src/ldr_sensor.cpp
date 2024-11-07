/*
 * MecGrowMancer - ESP32-based Homestead/Farm/Garden/Home/Garage Manager
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 */
#include "ldr_sensor.h"

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
 */
int16_t readLDRAnalog() {
  int ldrValue = analogRead(LDR_PIN);

  // Safe values for analog reading
  if (ldrValue < 0 || ldrValue > 4095) {
    debugPrintln("ldr_sensor: values out of bounds");
    return -1;
  }

  return ldrValue;
}

/*
  Read LDR analog value with filtering.
  
  - Uses exponential moving average for smootth transitions.
  - const DRASTIC_CHANGE_THRESHOLD defines the magnitude of a drastic change.
  - Keep track of consecutive drastic changes and, 
    * If less than 3, ignore it [potential spike (e.g., flash, lightning, vehicle headlamps, etc)]
    * If 3 or more, accepts as genuine rapid light change (but limit rate)
  - const MAX_CHANGE limits the maximum allowed change per reading.
  
  So, this filter smooths normal variations and resists most transient spikes,
  while still allowing  significant, persistent light level changes (clouds, etc)
  
  @return Filtered LDR value, or -1 if read error occurs.
*/
int16_t readLDRAnalogFiltered() {
  static float filteredValue = -1;
  static int drasticChangeCount = 0;
  int16_t rawValue = readLDRAnalog();
  
  if (rawValue == -1) {
    return -1;
  }

  if (filteredValue < 0) {
    filteredValue = rawValue;
    return (int16_t)round(filteredValue);
  }

  float difference = abs(rawValue - filteredValue);

  if (difference > DRASTIC_CHANGE_THRESHOLD) {
    drasticChangeCount++;
    if (drasticChangeCount >= 3) {
      // detect consistently drastic changes, but conmtinue with minimal impact
      filteredValue += (rawValue > filteredValue) ? MAX_CHANGE : -MAX_CHANGE;
      drasticChangeCount = 0;
    }
    // or maintain the previous filtered reading.
  } else {
    drasticChangeCount = 0;
    float newValue = (LDR_FILTER_ALPHA * rawValue) + ((1 - LDR_FILTER_ALPHA) * filteredValue);
    if (abs(newValue - filteredValue) > MAX_CHANGE) {
      filteredValue += (newValue > filteredValue) ? MAX_CHANGE : -MAX_CHANGE;
    } else {
      filteredValue = newValue;
    }
  }

  return (int16_t)round(filteredValue);
}
