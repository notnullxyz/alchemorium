/*
 * MecGrowMancer - ESP32-based Homestead/Farm/Garden/Home/Garage Manager
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 */

/**
 * This file mostly contains the configuration and tuning variables/parameters/directives.
 * These things controls timings and order, so if you change this, please test thrice.
 */

#include <Arduino.h>

// Custom module headers
#include "lcd_display.h"
#include "bmp280_sensor.h"
#include "rtc_module.h"
#include "serial_debug.h"
#include "scheduler.h"
#include "wifi_manager.h"

// Cooperative multitasking with configurable CPU yield - keeping this here for now until planned use.
const uint8_t CPU_THROTTLE_PERCENTAGE = 10;  // 10% throttle
const uint32_t LOOP_DELAY_MS = (100 * CPU_THROTTLE_PERCENTAGE) / 100;

// The period between LCD updates for known metrics (for the "dashboard" idle mode)
// in milliseconds.
const unsigned long LCD_UPDATE_INTERVAL = 1000;

