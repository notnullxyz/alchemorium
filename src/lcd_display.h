#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#define DEVICE_NAME "MecGrowMancer"
#define VERSION "v1.0"

void initLCD();
void displayLine(int line, const char* text);

#endif