#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#define DEVICE_NAME "MecGrowMancer"
#define VERSION "v1.1"
#define LCD_COLUMNS 16  // we use a 1602, 16 chars per line (2 lines)
#define LCD_ROWS 2
#define UPDATE_INTERVAL 3000  // ms interval for metrics rotation

void initLCD();
void displayLine(int line, const char* text);
void clearLine(int line);
void centerText(int line, const char* text);
void updateLCDDisplay();

// Declare these as external functions
extern float readTemperature();
extern float readPressure();

#endif