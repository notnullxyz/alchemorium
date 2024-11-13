/*
 * Alchemorium - ESP32-based Environmental Monitoring and Research Station
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 */

#include "serial_debug.h"

static DebugLevel currentDebugLevel = DEBUG_INFO;

void initDebug(long baudRate) {
  Serial.begin(baudRate);
  while (!Serial) {
    ;  // Wait for serial port to connect
  }
}

void setDebugLevel(DebugLevel level) {
  currentDebugLevel = level;

}

void debugPrint(const char* message, DebugLevel level) {
  if (level <= currentDebugLevel) {
    Serial.print(message);
  }
}

// use like: debugPrintln("System initialized", DEBUG_INFO);
void debugPrintln(const char* message, DebugLevel level) {
  if (level <= currentDebugLevel) {
    Serial.println(message);
  }
}

// use like: debugPrintf(DEBUG_VERBOSE, "Sensor reading: %d", sensorValue);
void debugPrintf(DebugLevel level, const char* format, ...) {
  if (level <= currentDebugLevel) {
    char buf[128];  // Adjust size as needed
    va_list args;
    va_start(args, format);
    vsnprintf(buf, sizeof(buf), format, args);
    va_end(args);
    Serial.print(buf);
  }
}
