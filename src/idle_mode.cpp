#include "idle_mode.h"
#include "lcd_display.h"
#include "bmp280_sensor.h"
#include "serial_debug.h"

void updateIdleDisplay() {
    float temp = readTemperature();
    float pressure = readPressure();
    
    char line1[17], line2[17];
    if (temp > -999) {
        snprintf(line1, sizeof(line1), "Temp: %.2f  'C", temp);
    } else {
        snprintf(line1, sizeof(line1), "Temp: Err");
    }
    
    if (pressure > -999) {
        snprintf(line2, sizeof(line2), "Pres: %.1f hPa", pressure);
    } else {
        snprintf(line2, sizeof(line2), "Pres: Err");
    }
    
    displayLine(0, line1);
    displayLine(1, line2);
    
    debugPrintln("Idle display updated", DEBUG_VERBOSE);
}
