/*
 * Alchemorium - ESP32-based Environmental Monitoring and Research Station
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 */

#ifndef LCD_CUSTOM_CHARS_H
#define LCD_CUSTOM_CHARS_H

#include <stdint.h>
#include <string.h>  // For memcpy
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

// Define custom character codes
#define CHAR_THERMOMETER 0
// #define CHAR_HUMIDITY 1
// #define CHAR_LIGHT 2
#define CHAR_FILL 3
#define CHAR_PRESSURE 4
#define CHAR_CELSIUS 5

// Custom character definitions - using https://chareditor.com/ as an aid
const uint8_t THERMOMETER_CONST[8] = {
  0b00100,
  0b01010,
  0b01010,
  0b01110,
  0b01110,
  0b11111,
  0b11111,
  0b01110
};

const uint8_t HUMIDITY_CONST[8] = {
  0b00100,
  0b00100,
  0b01010,
  0b01010,
  0b10001,
  0b10001,
  0b10001,
  0b01110
};

// const uint8_t LIGHT_CONST[8] = {
//   0b00000,
//   0b10101,
//   0b01110,
//   0b11111,
//   0b01110,
//   0b10101,
//   0b00000,
//   0b00000
// };

const uint8_t FILL_CONST[8] = {
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};

const uint8_t PRESSURE_CONST[8] = {
  0b00100,
  0b01110,
  0b10101,
  0b10001,
  0b10001,
  0b10001,
  0b01110,
  0b00100
};

const uint8_t CELSIUS_CONST[8] = {
	0b10000,
	0b00111,
	0b01000,
	0b01000,
	0b01000,
	0b01000,
	0b00111,
	0b00000
};

void initCustomChars(LiquidCrystal_I2C& lcd);

#endif  // LCD_CUSTOM_CHARS_H
