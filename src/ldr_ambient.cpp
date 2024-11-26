/*
 * Alchemorium - ESP32-based Environmental Monitoring and Research Station
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 */
#include "ldr_ambient.h"

int darknessCounter = 0;

void handleLCDBacklight();

bool initAmbientLightSensor()
{
  pinMode(LDR_PIN, INPUT);
  debugPrintln("ldr_ambient: init", DEBUG_VERBOSE);
  return true;
}

// Read and Set the light level.
void evaluateLightConditions()
{
  int lightLevel = analogRead(LDR_PIN);
  lastLightLevel = lightLevel; // Update the last light level

  debugPrintf(DEBUG_INFO, "ldr_ambient: evaluateLightConditions(): Light/Analog value: %d\n", lightLevel);

  // actions based on light levels
  handleLCDBacklight();
  // todo handleDeviceSleepMode();
}

// accessor for last collected light level
int getLastLightLevel()
{
  return lastLightLevel;
}

// Turn the LCD Backlight off when it's really dark, or on when it's not.
// This is really to prevent eye-broiling at night.
void handleLCDBacklight()
{
  static bool isBacklightOn = true;
  static int darknessCounter = 0;
  int lightLevel = getLastLightLevel();

  if (lightLevel > LDR_THRESHOLD)
  {
    darknessCounter++;
    if (darknessCounter >= CONFIDENCE && isBacklightOn)
    {
      toggleLCDBacklight(false);
      isBacklightOn = false;
      debugPrintln("ldr_ambient: handleLCDBacklight: Backlight OFF", DEBUG_VERBOSE);
      darknessCounter = 0;
    }
  }
  else
  {
    darknessCounter++;
    if (darknessCounter >= CONFIDENCE && !isBacklightOn)
    {
      toggleLCDBacklight(true);
      isBacklightOn = true;
      debugPrintln("ldr_ambient: handleLCDBacklight: Backlight ON", DEBUG_VERBOSE);
      darknessCounter = 0;
    }
  }

  // reset darknessCounter if the light changes before reaching CONFIDENCE
  if ((lightLevel > LDR_THRESHOLD && !isBacklightOn) || (lightLevel <= LDR_THRESHOLD && isBacklightOn))
  {
    darknessCounter = 0;
  }
}
