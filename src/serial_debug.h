/*
 * MecGrowMancer - ESP32-based Homestead/Farm/Garden/Home/Garage Manager
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 */

#ifndef SERIAL_DEBUG_H
#define SERIAL_DEBUG_H

#include <Arduino.h>

// Debug levels
enum DebugLevel {
  DEBUG_NONE,
  DEBUG_ERROR,
  DEBUG_WARNING,
  DEBUG_INFO,
  DEBUG_VERBOSE
};

// Function declarations
void initDebug(long baudRate = 115200);
void setDebugLevel(DebugLevel level);
void debugPrint(const char* message, DebugLevel level = DEBUG_INFO);
void debugPrintln(const char* message, DebugLevel level = DEBUG_INFO);
void debugPrintf(DebugLevel level, const char* format, ...);

#endif
