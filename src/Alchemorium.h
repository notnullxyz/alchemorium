/*
 * Alchemorium - ESP32-based Environmental Monitoring and Research Station
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 */

/**
 * This file mostly contains the configuration and tuning variables/parameters/directives.
 * These things controls timings and order, so if you change this, please test thrice.
 */

#include <Arduino.h>

// Custom module headers
#include "config.h"
#include "lcd_display.h"
#include "bmp280_sensor.h"
#include "rtc_module.h"
#include "serial_debug.h"
#include "scheduler.h"
#include "wifi_manager.h"
#include "sensor_data.h"
#include "ldr_ambient.h"
#include "websrv.h"

// Cooperative multitasking with configurable CPU yield
// While not really x% (depends on other things happening in the loop) it reasonably helps with reduction for infrequent tasks.
const uint8_t CPU_THROTTLE_PERCENTAGE = 5;  // 5% throttle
const uint32_t LOOP_DELAY_MS = (100 * CPU_THROTTLE_PERCENTAGE) / 100;
