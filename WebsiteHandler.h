#ifndef WEBSITEHANDLER__H
#define WEBSITEHANDLER__H

#include <ESPAsyncWebServer.h>
#include "Configuration.h"
#include "Display.h"

bool active = true;
String special = "";

class WebsiteHandler : public AsyncWebHandler {
public:
  WebsiteHandler() {}
  virtual ~WebsiteHandler() {}

  bool canHandle(AsyncWebServerRequest *request) { return true; }

  void handleRequest(AsyncWebServerRequest *request) {
    Serial.print("request on sta: ");
    Serial.println(request->url());

    if (request->method() == HTTP_GET)
      handleGetRequest(request);

    if (request->method() == HTTP_PUT)
      handlePutRequest(request);
  }

private:
  void handleGetRequest(AsyncWebServerRequest* request) {
    if (request->url() == "/logged-out")
      return request->send(SPIFFS, "/logout.html");

    if (!request->authenticate(config.username().c_str(), config.password().c_str()))
      return request->requestAuthentication();

    if (request->url() == "/")
      request->send(SPIFFS, "/index.html", "text/html", false, getValue);

    if (request->url() == "/style.css")
      request->send(SPIFFS, "/style.css", "text/css");
  }

  void handlePutRequest(AsyncWebServerRequest* request) {
    if (!request->authenticate(config.username().c_str(), config.password().c_str()))
      return request->requestAuthentication();

    Serial.print("value: ");
    Serial.println(request->getParam("value")->value());

    if (request->url() == "/active")
      active = request->getParam("value")->value() == "true";
    if (request->url() == "/color")
      config.setColor(Color::parse(request->getParam("value")->value()));
    if (request->url() == "/startup_time")
      setStartupTime(request->getParam("value")->value());
    if (request->url() == "/shutdown_time")
      setShutdownTime(request->getParam("value")->value());
    if (request->url() == "/auto_brightness")
      config.setAutoBrightness(request->getParam("value")->value() == "true");
    if (request->url() == "/utc_offset")
      config.setUtcOffset(request->getParam("value")->value().toInt());
    if (request->url() == "/reset")
      reset();
    if (request->url() == "/special")
      setSpecial(request->getParam("value")->value());

    request->send(200);
  }
  
  void setShutdownTime(String a_str) {
    config.setShutdownTime(Time::parseMinString(a_str));
    active = config.isActiveTime(rtc.read());
  }

  void setStartupTime(String a_str) {
    config.setStartupTime(Time::parseMinString(a_str));
    active = !config.isActiveTime(rtc.read());
  }
  
  void setSpecial(const String& a_special) {
    if(a_special == "") {
      special = a_special;
      special = "";
    }
    
    for(auto it = specials.begin(); it != specials.end(); it++)
      if (it->first == a_special)
        special = a_special;
  }

  void reset() {
    active = true;
    config.setStartupTime(Time());
    config.setShutdownTime(Time());
    config.setColor(Color(255, 255, 255));
  }

private:
  static String getValue(const String& a_var) {
    if (a_var == "STATE")
      return active ? "checked" : "";
    if (a_var == "STARTUP_TIME")
      return config.startupTime().toMinString();
    if (a_var == "SHUTDOWN_TIME")
      return config.shutdownTime().toMinString();
    if (a_var == "AUTO_BRIGHTNESS")
      return config.autoBrightness() ? "checked" : "";
    if (a_var == "COLOR")
      return config.color().toString();
    if (a_var == "UTC_OFFSET")
      return String(config.utcOffset());
    if (a_var == "POSSIBLE_SPECIALS")
      return "[\"heart\", \"kati\", \"andi\"]";
    return "INVALID";
  }
};

#endif
