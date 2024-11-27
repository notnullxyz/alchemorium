/*
 * Alchemorium - ESP32-based Environmental Monitoring and Research Station
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 */

#include "websrv.h"
#include "lcd_display.h"
#include "FS.h"         // Include the FS library for file handling
#include "SPIFFS.h"     // Include SPIFFS library

WebServer server(HTTPD_PORT);

void toggleLCDBacklightEndpoint();

void handleRoot() {
    debugPrintln("websrv: handleRoot", DEBUG_VERBOSE);
    
    File file = SPIFFS.open("/index.html", "r");
    if (!file) {
        debugPrintln("websrv: handleRoot error opening index.html", DEBUG_ERROR);
        server.send(404, "text/plain", "File Not Found");
        return;
    }
    
    server.streamFile(file, "text/html");
    file.close();
}

void handleSensorData() {
    debugPrintln("websrv: handleSensorData", DEBUG_VERBOSE);
    
    // Use a buffer for JSON
    char json[64];
    snprintf(json, sizeof(json), "{\"temperature\":%.2f,\"pressure\":%.2f}", 
             g_sensorData.temperature, g_sensorData.pressure);
    
    server.send(200, "application/json", json);
}

void initWebServer() {
    if (!isWiFiConnected()) {
        debugPrintln("webserver: WiFi not connected, cannot start server", DEBUG_ERROR);
        return;
    }

    server.on("/", handleRoot);
    server.on("/sensor_data", handleSensorData);
    server.on("/toggle_backlight", toggleLCDBacklightEndpoint);

    server.begin();
    debugPrintln("websrv: Server started", DEBUG_INFO);
}

void toggleLCDBacklightEndpoint() {
    static bool backlightState = true; // Initial state
    backlightState = !backlightState;
    toggleLCDBacklight(backlightState);
    server.send(200, "text/plain", "LCD Backlight toggled");
}


void handleClientRequests() {
  server.handleClient();
}
