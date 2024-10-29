#include "lcd_display.h"
#include <LiquidCrystal.h>
#include "serial_debug.h"

// Initialize the library with the numbers of the interface pins
const int rs = 19, en = 23, d4 = 18, d5 = 17, d6 = 16, d7 = 15;  // TODO clean up var mem
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void selfTest();
void displayDeviceInfo();

void initLCD() {
  lcd.begin(16, 2);  // Set up the LCD's number of columns and rows
  debugPrintln("LCD initialized. Starting self-test and greeting.", DEBUG_INFO);
  selfTest();
  displayDeviceInfo();
}

void displayLine(int line, const char* text) {
  lcd.setCursor(0, line);
  lcd.print(text);
  debugPrintf(DEBUG_VERBOSE, "Displayed on LCD line %d: %s\n", line, text);
}

// A test cycle across the 16x2 screen we use - during setup()
void selfTest() {
  byte testChar[8] = {
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111
  };

  lcd.createChar(0, testChar);
  lcd.clear();

  // Roll on: Fill the screen
  for (int i = 0; i < 32; ++i) {  // 16 cols * 2 rows
    int row = i / 16;             // Calculate row (0 or 1)
    int col = i % 16;             // Calculate column (0 to 15)
    lcd.setCursor(col, row);
    lcd.write(byte(0));  // Write the testChar
    delay(20);
  }

  delay(300);  // Hold the display filled for a moment

  // Roll off: Clear the screen
  for (int i = 0; i < 16; ++i) {
    // Clear from the end of the first row
    lcd.setCursor(15 - i, 0);
    lcd.write(' ');  // Clear character by writing a space

    // Clear from the start of the second row
    lcd.setCursor(i, 1);
    lcd.write(' ');  // Clear character by writing a space

    delay(25);
  }
}

// hello
void displayDeviceInfo() {
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print(DEVICE_NAME);
  delay(70);

  // Center the version on the second line
  for (int i = 0; i < 6; ++i) {
    lcd.setCursor(0, 1);
    lcd.print("                ");
    delay(80);
    lcd.setCursor(6, 1);  // centering
    lcd.print(VERSION);
    delay(80);
  }
  delay(500);
  lcd.clear();
}
