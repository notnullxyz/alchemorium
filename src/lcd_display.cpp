#include "lcd_display.h"
#include <LiquidCrystal_I2C.h>
#include "serial_debug.h"
#include "lcd_custom_chars.h"
#include "bmp280_sensor.h"
#include <time.h>
#include "src/rtc_module.h"

// Initialize the library with the address and cols/rows
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

void initLCD() {
  lcd.init();
  lcd.backlight();
  debugPrintln("LCD initialized. Starting self-test and greeting.", DEBUG_INFO);
  initCustomChars(lcd);
  selfTest();
  displayDeviceInfo();
}

void displayLine(int line, const char* text) {
  if (line < 0 || line >= LCD_ROWS) {
    debugPrintln("Invalid LCD line", DEBUG_ERROR);
    return;
  }
  clearLine(line);
  lcd.setCursor(0, line);
  lcd.print(text);
  debugPrintf(DEBUG_VERBOSE, "Displayed on LCD line %d: %s\n", line, text);
}

void clearLine(int line) {
  if (line < 0 || line >= LCD_ROWS) {
    debugPrintln("Invalid LCD line", DEBUG_ERROR);
    return;
  }
  lcd.setCursor(0, line);
  for (int i = 0; i < LCD_COLUMNS; i++) {
    lcd.print(" ");
  }
}

void centerText(int line, const char* text) {
  int textLength = strlen(text);
  int padding = (LCD_COLUMNS - textLength) / 2;
  if (padding < 0) padding = 0;
  clearLine(line);
  lcd.setCursor(padding, line);
  lcd.print(text);
}

void updateLCDDisplay() {
  unsigned long currentTime = millis();

  // update time on top row.
  updateTimeDisplay();

  // Update the metric display every UPDATE_INTERVAL
  if (currentTime - lastUpdateTime >= UPDATE_INTERVAL) {
    updateMetricDisplay();
    lastUpdateTime = currentTime;
    currentState = static_cast<MetricState>((currentState + 1) % STATE_COUNT);
  }
}

// A test cycle across the 16x2 screen we use - during setup()
void selfTest() {
  lcd.clear();

  // Roll on: Fill the screen
  for (int i = 0; i < (LCD_COLUMNS * LCD_ROWS); ++i) {  // 16 cols * 2 rows
    int row = i / LCD_COLUMNS;                          // Calculate row (0 or 1)
    int col = i % LCD_COLUMNS;                          // Calculate column (0 to 15)
    lcd.setCursor(col, row);
    lcd.write(byte(CHAR_FILL));  // Test by filling all pixels
    delay(22);
  }

  delay(500);  // Hold the display filled for a moment

  // Roll off: Clear the screen
  for (int i = 0; i < LCD_COLUMNS; ++i) {
    // Clear from the end of the first row
    lcd.setCursor(15 - i, 0);
    lcd.write(' ');  // clear one char
    lcd.setCursor(i, 1);
    lcd.write(' ');

    delay(24);
  }
}

// hello there
void displayDeviceInfo() {
  lcd.clear();
  centerText(0, DEVICE_NAME);
  delay(70);
  centerText(1, VERSION);
  delay(500);
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


void updateMetricDisplay() {
  clearLine(1);
  lcd.setCursor(0, 1);

  switch (currentState) {
    case TEMP:
      lcd.write(byte(CHAR_THERMOMETER));
      lcd.print(" ");
      lcd.print(readTemperature());
      lcd.print("C");
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
