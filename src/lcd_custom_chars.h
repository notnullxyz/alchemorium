/*
 * Alchemorium - ESP32-based Environmental Monitoring and Research Station
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 */

#include <stdint.h>

#ifndef LCD_CUSTOM_CHARS_H
#define LCD_CUSTOM_CHARS_H

#include <string.h>  // For memcpy

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
  B11000,
  B11000,
  B00000,
  B00111,
  B00100,
  B00100,
  B00111,
  B00000
};

void initCustomChars(LiquidCrystal_I2C& lcd) {
  uint8_t thermometer[8];
  //uint8_t humidity[8];
  //uint8_t light[8];
  uint8_t fill[8];
  uint8_t pressure[8];
  uint8_t celsius[8];

  memcpy(thermometer, THERMOMETER_CONST, 8);
  //memcpy(humidity, HUMIDITY_CONST, 8);
  //memcpy(light, LIGHT_CONST, 8);
  memcpy(fill, FILL_CONST, 8);
  memcpy(pressure, PRESSURE_CONST, 8);
  memcpy(celsius, CELSIUS_CONST, 8);

  lcd.createChar(CHAR_THERMOMETER, thermometer);
  //lcd.createChar(CHAR_HUMIDITY, humidity);
  //lcd.createChar(CHAR_LIGHT, light);
  lcd.createChar(CHAR_FILL, fill);
  lcd.createChar(CHAR_PRESSURE, pressure);
  lcd.createChar(CHAR_CELSIUS, celsius);

}

#endif  // LCD_CUSTOM_CHARS_H
