#pragma once

#include <ESPAsyncWebServer.h>

class AccessPointHandler : public AsyncWebHandler {
public:
  AccessPointHandler() {}
  virtual ~AccessPointHandler() {}

  bool canHandle(AsyncWebServerRequest *request) { return true; }

  void handleRequest(AsyncWebServerRequest *request) {
    Serial.print("request on ap: ");
    Serial.println(request->url());

    if (request->url() == "/submit")
      onSubmit(request);

    request->send(SPIFFS, "/credentials.html", "text/html", false, getValue);
  }

private:
  void onSubmit(AsyncWebServerRequest* a_request) {
    if (a_request->hasParam("ssid"))
      config.setWiFiSsid(a_request->getParam("ssid")->value());
    if (a_request->hasParam("password"))
      config.setWiFiPassword(a_request->getParam("password")->value());
    WiFi.begin(config.wiFiSsid().c_str(), config.wiFiPassword().c_str());
  }

private:
  static String getValue(const String& a_var) {
    if (a_var == "SSID")
      return config.wiFiSsid();
    if (a_var == "PASSWORD")
      return config.wiFiPassword();
    return "INVALID";
  }
};
