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
  config.m_httpUsername = doc["http_username"].as<String>();
  config.m_httpPassword = doc["http_password"].as<String>();
  config.m_startupTime = Time::parseMinString(doc["startup_time"]);
  config.m_shutdownTime = Time::parseMinString(doc["shutdown_time"]);
  config.m_color = Color::parse(doc["color"]);
  config.m_adaptiveLuminosity = doc["adaptive_luminosity"];
  config.m_wifiSsid = doc["wifi_ssid"].as<String>();
  config.m_wifiPassword = doc["wifi_password"].as<String>();
  return config;
}

void Configuration::save() {
  doc["utc_offset"] = utcOffset();
  doc["http_username"] = httpUsername();
  doc["http_password"] = httpPassword();
  doc["startup_time"] = startupTime().toMinString();
  doc["shutdown_time"] = shutdownTime().toMinString();
  doc["color"] = color().toString();
  doc["adaptive_luminosity"] = adaptiveLuminosity();
  doc["wifi_ssid"] = wifiSsid();
  doc["wifi_password"] = wifiPassword();

  auto file = SPIFFS.open("/config.json", FILE_WRITE);
  if (!file) Serial.println("failed to write config");
  serializeJsonPretty(doc, file);
  file.close();
}
