#include "Configuration.h"
#include <ArduinoJson.h>
#include <SPIFFS.h>
#include <FS.h>

Configuration config;
StaticJsonDocument<1024> doc;

Configuration Configuration::load() {
  auto file = SPIFFS.open("/config.json", FILE_READ);
  if (!file) Serial.println("failed to read config");
  deserializeJson(doc, file);
  file.close();

  Configuration config;
  config.m_utcOffset = doc["utc_offset"];
  config.m_username = doc["username"].as<String>();
  config.m_password = doc["password"].as<String>();
  config.m_startupTime = Time::parseMinString(doc["startup_time"]);
  config.m_shutdownTime = Time::parseMinString(doc["shutdown_time"]);
  config.m_color = Color::parse(doc["color"]);
  config.m_autoBrightness = doc["auto_brightness"];
  config.m_wiFiSsid = doc["wifi_ssid"].as<String>();
  config.m_wiFiPassword = doc["wifi_password"].as<String>();
  return config;
}

void Configuration::save() {
  doc["utc_offset"] = utcOffset();
  doc["username"] = username();
  doc["password"] = password();
  doc["startup_time"] = startupTime().toMinString();
  doc["shutdown_time"] = shutdownTime().toMinString();
  doc["color"] = color().toString();
  doc["auto_brightness"] = autoBrightness();
  doc["wifi_ssid"] = wiFiSsid();
  doc["wifi_password"] = wiFiPassword();

  auto file = SPIFFS.open("/config.json", FILE_WRITE);
  if (!file) Serial.println("failed to write config");
  serializeJson(doc, file);
  file.close();
}
