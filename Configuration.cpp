#include "Configuration.h"
#include <ArduinoJson.h>
#include <SPIFFS.h>
#include <FS.h>

StaticJsonDocument<1024> doc;

Configuration Configuration::load() {
  SPIFFS.begin(true);
  auto file = SPIFFS.open("/config.json", FILE_READ);
  if (!file) Serial.println("failed to read config");
  Serial.println("Configuration: ");
  Serial.println(file.readString());
  file.seek(0);
  deserializeJson(doc, file);
  file.close();

  Configuration config;
  config.m_utcOffset = doc["utc_offset"];
  config.m_name = doc["name"].as<String>();
  config.m_password = doc["password"].as<String>();
  config.m_startupTime = Time::parseMinString(doc["startup_time"]);
  config.m_shutdownTime = Time::parseMinString(doc["shutdown_time"]);
  config.m_foregroundColor = Color::parse(doc["foreground_color"]);
  config.m_adaptiveLuminosity = doc["adaptive_luminosity"];
  config.m_wifiSsid = doc["wifi_ssid"].as<String>();
  config.m_wifiPassword = doc["wifi_password"].as<String>();
  return config;
}

void Configuration::save() {
  doc["utc_offset"] = utcOffset();
  doc["name"] = name();
  doc["password"] = password();
  doc["startup_time"] = Time::toMinString(startupTime());
  doc["shutdown_time"] = Time::toMinString(shutdownTime());
  doc["foreground_color"] = Color::toString(foregroundColor());
  doc["adaptive_luminosity"] = adaptiveLuminosity();
  doc["wifi_ssid"] = wifiSsid();
  doc["wifi_password"] = wifiPassword();

  auto file = SPIFFS.open("/config.json", FILE_WRITE);
  if (!file) Serial.println("failed to write config");
  serializeJsonPretty(doc, file);
  file.close();
}
