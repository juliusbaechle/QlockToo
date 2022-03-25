#pragma once

#include <WiFi.h>
#include <SPIFFS.h>
#include <AsyncTCP.h>
#include <DNSServer.h>
#include "WebsiteHandler.h"
#include "AccessPointHandler.h"

DNSServer dnsServer;
AsyncWebServer server(80);

void setWiFiMode(bool a_disconnected) {
  static bool lastState = false;
  if (lastState == a_disconnected) return;
  lastState = a_disconnected;

  if (a_disconnected) {
    Serial.println("enabled access point mode");
    WiFi.mode(WIFI_AP);
    WiFi.softAP("QlockTwo", "QlockTwo");
    dnsServer.start(53, "*", WiFi.softAPIP());
  } else {
    Serial.println("enabled station mode");
    WiFi.mode(WIFI_STA);
    WiFi.setHostname("QlockTwo");
    dnsServer.stop();
  }
}

void setupServer() {
  if (!SPIFFS.begin(true))
    Serial.println("An Error has occurred while mounting SPIFFS");

  WiFi.begin();

  server.addHandler(new WebsiteHandler()).setFilter(ON_STA_FILTER);
  server.addHandler(new AccessPointHandler()).setFilter(ON_AP_FILTER);
  server.begin();
}
