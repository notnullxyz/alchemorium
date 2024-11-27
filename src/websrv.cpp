/*
 * Alchemorium - ESP32-based Environmental Monitoring and Research Station
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 */

#include "websrv.h"

WebServer server(HTTPD_PORT);

void handleRoot() {
  debugPrintln("websrv: handleroot", DEBUG_VERBOSE);
  server.send(200, "text/plain", "Welcome to Alchemorium Web Server!");
}

void handleSensorData() {
  debugPrintln("websrv: handleSensorData", DEBUG_VERBOSE);
  String json = "{";
  json += "\"temperature\":" + String(g_sensorData.temperature) + ",";
  json += "\"pressure\":" + String(g_sensorData.pressure);
  json += "}";

  server.send(200, "application/json", json);
}

void initWebServer() {
  if (!isWiFiConnected()) {
    debugPrintln("webserver: WiFi not connected, cannot start server", DEBUG_ERROR);
    return;
  }

  server.on("/", handleRoot);
  server.on("/sensor_data", handleSensorData);

  server.begin();
  debugPrintln("websrv: Server started", DEBUG_INFO);
}

void handleClientRequests() {
  server.handleClient();
}
