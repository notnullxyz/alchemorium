#include "lcd_display.h"
#include <LiquidCrystal.h>
#include "serial_debug.h"
#include "lcd_custom_chars.h"
#include <time.h>

// Initialize the library with the numbers of the interface pins
const int rs = 19, en = 23, d4 = 18, d5 = 17, d6 = 16, d7 = 15;  // TODO clean up var mem
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

enum MetricState {
  TEMP,
  HUMIDITY,
  LIGHT,
  STATE_COUNT
};

static MetricState currentState = TEMP;
static unsigned long lastUpdateTime = 0;
const unsigned long UPDATE_INTERVAL = 3000;  // 3sec

void selfTest();
void displayDeviceInfo();
void updateTimeDisplay();
void updateMetricDisplay();

void initLCD() {
  lcd.begin(16, 2);  // Set up the LCD's number of columns and rows
  debugPrintln("LCD initialized. Starting self-test and greeting.", DEBUG_INFO);
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
  
  // Update time on row 0 of the lcd
  updateTimeDisplay();
  
  // update display of metrics every UPDATE_INTERVAL
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
  for (int i = 0; i < 32; ++i) {  // 16 cols * 2 rows
    int row = i / 16;             // Calculate row (0 or 1)
    int col = i % 16;             // Calculate column (0 to 15)
    lcd.setCursor(col, row);
    lcd.write(byte(CHAR_FILL));   // Test by filling all pixels
    delay(16);
  }

  delay(350);  // Hold the display filled for a moment

  // Roll off: Clear the screen
  for (int i = 0; i < 16; ++i) {
    // Clear from the end of the first row
    lcd.setCursor(15 - i, 0);
    lcd.write(' ');  // Clear character by writing a space

    // Clear from the start of the second row
    lcd.setCursor(i, 1);
    lcd.write(' ');  // Clear character by writing a space

    delay(19);
  }
}

// hello there
void displayDeviceInfo() {
  lcd.clear();
  // lcd.setCursor(2, 0);
  // lcd.print(DEVICE_NAME);
  centerText(0, DEVICE_NAME);
  delay(70);

  // Center the version on the second line
  /**for (int i = 0; i < 6; ++i) {
    lcd.setCursor(0, 1);
    lcd.print("                ");
    delay(80);
    lcd.setCursor(6, 1);  // centering
    lcd.print(VERSION);
    delay(80);
  }*/

  centerText(1, VERSION);
  delay(500);
  lcd.clear();
}

void updateTimeDisplay() {
  time_t now;
  struct tm timeinfo;
  time(&now);
  localtime_r(&now, &timeinfo);
  
  char timeStr[17];
  strftime(timeStr, sizeof(timeStr), "%H:%M:%S %d/%m", &timeinfo);
  
  lcd.setCursor(0, 0);
  lcd.print(timeStr);
}

void updateMetricDisplay() {
  clearLine(1);
  lcd.setCursor(0, 1);
  
  switch(currentState) {
    case TEMP:
      lcd.write(byte(CHAR_THERMOMETER));
      lcd.print(" ");
      lcd.print(getTemperature());
      lcd.print("C");
      break;
    case HUMIDITY:
      lcd.write(byte(CHAR_HUMIDITY));
      lcd.print(" ");
      lcd.print(getHumidity());
      lcd.print("%");
      break;
    case LIGHT:
      lcd.write(byte(CHAR_LIGHT));
      lcd.print(" ");
      lcd.print(getLightLevel());
      lcd.print("lux");
      break;
    // and so forth
  }
}

