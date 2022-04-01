#include "AccessPointHandler.h"
#include <SPIFFS.h>
#include <WiFi.h>

void AccessPointHandler::handleRequest(AsyncWebServerRequest *request) {
  Serial.print("request on ap: ");
  Serial.println(request->url());

  if (request->url() == "/submit")
    onSubmit(request);

  request->send(SPIFFS, "/credentials.html", "text/html", false, [this](String str) { return getValue(str); });
}

void AccessPointHandler::onSubmit(AsyncWebServerRequest* a_request) {
  if (a_request->hasParam("ssid"))
    m_qlock.setWifiSsid(a_request->getParam("ssid")->value());
  if (a_request->hasParam("password"))
    m_qlock.setWifiPassword(a_request->getParam("password")->value());
  WiFi.begin(m_qlock.wifiSsid().c_str(), m_qlock.wifiPassword().c_str());
}

String AccessPointHandler::getValue(const String& a_var) {
  if (a_var == "SSID")
    return m_qlock.wifiSsid();
  if (a_var == "PASSWORD")
    return m_qlock.wifiPassword();
  return "INVALID";
}