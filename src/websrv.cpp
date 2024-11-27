/*
 * Alchemorium - ESP32-based Environmental Monitoring and Research Station
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 */

#include "websrv.h"
#include "lcd_display.h"

WebServer server(HTTPD_PORT);

void toggleLCDBacklightEndpoint();

void handleRoot() {
    debugPrintln("websrv: handleRoot", DEBUG_VERBOSE);
    
    char html[1024];
    snprintf(html, sizeof(html),
        "<html><head><title>Alchemorium Dashboard</title>"
        "<script>function fetchData() {"
        "fetch('/sensor_data')"
        ".then(response => response.json())"
        ".then(data => {"
        "document.getElementById('temperature').innerText = data.temperature + ' &deg;C';"
        "document.getElementById('pressure').innerText = data.pressure + ' hPa';"
        "});"
        "}"
        "setInterval(fetchData, 5000);"
        "</script></head><body>"
        "<h1>Alchemorium Dashboard</h1>"
        "<p>Temperature: <span id='temperature'>Loading...</span></p>"
        "<p>Pressure: <span id='pressure'>Loading...</span></p>"
        "<button onclick='toggleBacklight()'>Toggle LCD Backlight</button>"
        "<script>function toggleBacklight() {fetch('/toggle_backlight');}</script>"
        "</body></html>", 
        g_sensorData.temperature, g_sensorData.pressure);
    
    server.send(200, "text/html", html);
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
