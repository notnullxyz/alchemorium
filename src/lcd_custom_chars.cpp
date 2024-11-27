/*
 * Alchemorium - ESP32-based Environmental Monitoring and Research Station
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 */

#include "lcd_custom_chars.h"

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
