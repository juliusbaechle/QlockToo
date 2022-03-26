#pragma once

#include <ESPAsyncWebServer.h>
#include "Configuration.h"

bool shutdown = false;

class WebsiteHandler : public AsyncWebHandler {
public:
  WebsiteHandler() {}
  virtual ~WebsiteHandler() {}

  bool canHandle(AsyncWebServerRequest *request) { return true; }

  void handleRequest(AsyncWebServerRequest *request) {
    Serial.print("request on sta: ");
    Serial.println(request->url());

    if (request->url() == "/logged-out")
      return request->send(SPIFFS, "/logout.html");

    if (!request->authenticate(config.username().c_str(), config.password().c_str()))
      return request->requestAuthentication();

    if(request->url() == "/style.css")
      return request->send(SPIFFS, "/style.css", "text/css");

    if (request->url() == "/on")
      shutdown = false;
    if (request->url() == "/off")
      shutdown = true;
    if (request->url() == "/color")
      setColor(request);
    if (request->url() == "/startup_time")
      setStartupTime(request->getParam("value")->value());
    if (request->url() == "/shutdown_time")
      setShutdownTime(request->getParam("value")->value());
    if (request->url() == "/auto_brightness")
      config.setAutoBrightness(request->getParam("value")->value() == "true");
    if (request->url() == "/reset")
      reset();

    request->send(SPIFFS, "/index.html", "text/html", false, getValue);
  }

private:
  void setColor(AsyncWebServerRequest *request) {
    Serial.print("received ");
    Serial.print(request->params());
    Serial.print(", ");
    Serial.println(request->hasParam("value"));
    Serial.print(", ");
    Serial.println(request->getParam("value")->value());

    config.setColor(Color::parse(request->getParam("value")->value()));
  }

  void setShutdownTime(String a_str) {
    config.setShutdownTime(Time::parseMinString(a_str));
    shutdown = !config.isActiveTime(rtc.read());
  }

  void setStartupTime(String a_str) {
    config.setStartupTime(Time::parseMinString(a_str));
    shutdown = !config.isActiveTime(rtc.read());
  }
  
  void reset() {
    shutdown = false;
    config.setStartupTime(Time());
    config.setShutdownTime(Time());
    config.setColor(Color(255, 255, 255));
  }

private:
  static String getValue(const String& a_var) {
    if (a_var == "STATE")
      return shutdown ? "OFF" : "ON";
    if (a_var == "STARTUP_TIME")
      return config.startupTime().toMinString();
    if (a_var == "SHUTDOWN_TIME")
      return config.shutdownTime().toMinString();
    if (a_var == "AUTO_BRIGHTNESS")
      return config.autoBrightness() ? "checked" : "";
    if (a_var == "COLOR")
      return config.color().toString();
    return "INVALID";
  }
};
