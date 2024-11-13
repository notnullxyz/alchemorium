/*
 * Alchemorium - ESP32-based Environmental Monitoring and Research Station
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 */

#include "lcd_display.h"
#include <LiquidCrystal_I2C.h>
#include "serial_debug.h"
#include "lcd_custom_chars.h"
#include "bmp280_sensor.h"
#include <time.h>
#include "rtc_module.h"

// Init the lcd lib with the address and cols/rows
LiquidCrystal_I2C lcd(0x27, LCD_COLUMNS, LCD_ROWS);

enum MetricState {
  TEMP,
  HUMIDITY,
  LIGHT,
  PRESSURE,
  STATE_COUNT
};

static MetricState currentState = TEMP;
static unsigned long lastUpdateTime = 0;

void selfTest();
void displayDeviceInfo();
void updateTimeDisplay();
void updateMetricDisplay();

// Convenience for everything the specific lcd may need.
void initLCD() {
  lcd.init();
  lcd.backlight();
  debugPrintln("lcd: initialized. Starting self-test/intro", DEBUG_INFO);
  initCustomChars(lcd);
  selfTest();
  displayDeviceInfo();
}

// line display wrapper (line number, text)
void displayLine(int line, const char* text) {
  if (line < 0 || line >= LCD_ROWS) {
    debugPrintln("lcd: invalid LCD line", DEBUG_ERROR);
    return;
  }
  clearLine(line);
  lcd.setCursor(0, line);
  lcd.print(text);
  debugPrintf(DEBUG_VERBOSE, "Displayed on LCD line %d: %s\n", line, text);
}

// line clear wrapper (line number)
void clearLine(int line) {
  if (line < 0 || line >= LCD_ROWS) {
    debugPrintln("lcd: Invalid LCD line", DEBUG_ERROR);
    return;
  }
  lcd.setCursor(0, line);
  for (int i = 0; i < LCD_COLUMNS; i++) {
    lcd.print(" ");
  }
}

// centering text on lcd wrapper (line number, text)
void centerText(int line, const char* text) {
  int textLength = strlen(text);
  int padding = (LCD_COLUMNS - textLength) / 2;
  if (padding < 0) padding = 0;
  clearLine(line);
  lcd.setCursor(padding, line);
  lcd.print(text);
}

// Temporary notices (like "wifi connecting...")
void displayTemporaryMessage(const char* line1, const char* line2, unsigned long duration) {
  lcd.clear();
  centerText(0, line1);
  centerText(1, line2);
  delay(duration);
}

void updateLCDDisplay() {
  unsigned long currentTime = millis();

  // update time on top row.
  updateTimeDisplay();

  // Update the metrics display every UPDATE_INTERVAL
  if (currentTime - lastUpdateTime >= UPDATE_INTERVAL) {
    updateMetricDisplay();
    lastUpdateTime = currentTime;
    currentState = static_cast<MetricState>((currentState + 1) % STATE_COUNT);
  }
}

// A test cycle across the 16x2 screen we use - during setup()
// Hopefully enough to show if any parts of the screen is defective (important for alarms/warnings)
void selfTest() {
  lcd.clear();

  // Roll on: Fill the screen
  for (int i = 0; i < (LCD_COLUMNS * LCD_ROWS); ++i) {  // 16 cols * 2 rows
    int row = i / LCD_COLUMNS;                          // Calculate row (0 or 1)
    int col = i % LCD_COLUMNS;                          // Calculate column (0 to 15)
    lcd.setCursor(col, row);
    lcd.write(byte(CHAR_FILL));  // Test by filling all pixels
    delay(SELF_TEST_FILL_AND_CLEAR_DELAY);
  }

  delay(SELF_TEST_HOLD_DELAY);  // Hold the display filled for a moment

  // Roll off: Clear the screen
  for (int i = 0; i < LCD_COLUMNS; ++i) {
    // Clear from the end of the first row
    lcd.setCursor(15 - i, 0);
    lcd.write(' ');  // clear one char
    lcd.setCursor(i, 1);
    lcd.write(' ');

    delay(SELF_TEST_FILL_AND_CLEAR_DELAY);
  }
}

// hello there - device announcement after bootup
void displayDeviceInfo() {
  lcd.clear();
  centerText(0, DEVICE_NAME);
  delay(SELF_TEST_FILL_AND_CLEAR_DELAY * 2);
  centerText(1, VERSION);
  delay(SELF_TEST_HOLD_DELAY);
  lcd.clear();
}

// update time for the lcd, using a call to RTC
void updateTimeDisplay() {
  RtcDateTime now = getCurrentTime();
  char timeStr[17];
  snprintf(timeStr, sizeof(timeStr), "%02u:%02u:%02u %02u/%02u", 
           now.Hour(), now.Minute(), now.Second(), now.Day(), now.Month());
  lcd.setCursor(0, 0);
  lcd.print(timeStr);
}

// update the display metrics based on state
void updateMetricDisplay() {
  clearLine(1);
  lcd.setCursor(0, 1);

  switch (currentState) {
    case TEMP:
      lcd.write(byte(CHAR_THERMOMETER));
      lcd.print(" ");
      lcd.print(readTemperature());
      lcd.write(byte(CHAR_CELSIUS));
      break;
    case HUMIDITY:
      lcd.write(byte(CHAR_HUMIDITY));
      lcd.print(" ");
      lcd.print("??");  // still to do
      lcd.print("%");
      break;
    case LIGHT:
      lcd.write(byte(CHAR_LIGHT));
      lcd.print(" ");
      lcd.print("??");
      lcd.print("lux");
      break;
    case PRESSURE:
      lcd.write(byte(CHAR_PRESSURE));
      lcd.print(" ");
      lcd.print(readPressure());
      lcd.print("hPa");
      break;
      // and so forth.
  }
}
