/*
 * Alchemorium - ESP32-based Environmental Monitoring and Research Station
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 */
#include "ldr_ambient.h"

int darknessCounter = 0;

bool initAmbientLightSensor()
{
  pinMode(LDR_PIN, INPUT);
  debugPrintln("ldr_ambient: init", DEBUG_VERBOSE);
  return true;
}

void measureLightForLCD()
{
  static bool isBacklightOn = true; // Track the current state of the backlight
  int lightLevel = analogRead(LDR_PIN); // Read the analog value from the light sensor

  debugPrintf(DEBUG_INFO, "ldr_ambient: analog value = %d\n", lightLevel);

  if (lightLevel > LDR_THRESHOLD)
  {
    darknessCounter++;
    if (darknessCounter >= CONFIDENCE && isBacklightOn)
    {
      toggleLCDBacklight(false); // Turn off the backlight
      isBacklightOn = false;
      debugPrintln("ldr_ambient: Backlight turned OFF. Resetting state.", DEBUG_VERBOSE);
      darknessCounter = 0; // Reset after toggle
    }
  }
  else
  {
    darknessCounter++;
    if (darknessCounter >= CONFIDENCE && !isBacklightOn)
    {
      toggleLCDBacklight(true); // Turn on the backlight
      isBacklightOn = true;
      debugPrintln("ldr_ambient: Backlight turned ON. Resetting state.", DEBUG_VERBOSE);
      darknessCounter = 0; // Reset after toggle
    }
  }

  // Reset darknessCounter if the light condition changes before reaching CONFIDENCE
  if ((lightLevel > LDR_THRESHOLD && !isBacklightOn) || (lightLevel <= LDR_THRESHOLD && isBacklightOn))
  {
    darknessCounter = 0;
  }
}


