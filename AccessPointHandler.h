#pragma once

#include <ESPAsyncWebServer.h>

String ssid = "";
String password = "";

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
    Serial.print("Parameters: ");
    Serial.println(a_request->params());

    if (a_request->hasParam("ssid"))
      ssid = a_request->getParam("ssid")->value();
    if (a_request->hasParam("password"))
      password = a_request->getParam("password")->value();

    Serial.print("Set Credentials: ");
    Serial.print(ssid);
    Serial.print(", ");
    Serial.println(password);

    WiFi.begin(ssid.c_str(), password.c_str());
  }

private:
  static String getValue(const String& a_var) {
    if (a_var == "SSID")
      return ssid;
    if (a_var == "PASSWORD")
      return password;
    return "INVALID";
  }
};
