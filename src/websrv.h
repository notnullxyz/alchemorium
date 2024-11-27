/*
 * Alchemorium - ESP32-based Environmental Monitoring and Research Station
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 */

#ifndef WEBSRV_H
#define WEBSRV_H

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "wifi_manager.h"
#include "serial_debug.h"
#include "sensor_data.h"
#include "config.h"
#include "lcd_display.h"
#include "FS.h"         // Include the FS library for file handling
#include "SPIFFS.h"     // Include SPIFFS library

void initWebServer();
void handleClientRequests();

#endif
