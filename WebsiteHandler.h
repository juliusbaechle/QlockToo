#pragma once

#include <ESPAsyncWebServer.h>

// Benutzername und Passwort f�r Eingabseite
const char* http_username = "admin";
const char* http_password = "admin";

// Config set by Server
String color = "rot";
Time startupTime;
Time shutdownTime;
bool auto_brightness = true;
uint8_t manual_brightness = 255;
bool shutdown = false;

bool isDayTime(Time a_time) {
  if (startupTime < shutdownTime) {
    return startupTime < a_time && a_time < shutdownTime;
  } else {
    return startupTime < a_time || a_time < shutdownTime;
  }
}

bool updateNightTime(Time a_time) {
  if (a_time == shutdownTime)
    shutdown = true;
  if (a_time == startupTime)
    shutdown = false;
}

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

    if (!request->authenticate(http_username, http_password))
      return request->requestAuthentication();

    if(request->url() == "/style.css")
      return request->send(SPIFFS, "/style.css", "text/css");

    if (request->url() == "/on")
      shutdown = false;
    if (request->url() == "/off")
      shutdown = true;
    if (request->url() == "/white")
      color = "white";
    if (request->url() == "/red")
      color = "red";
    if (request->url() == "/green")
      color = "green";
    if (request->url() == "/blue")
      color = "blue";
    if (request->url() == "/purple")
      color = "purple";
    if (request->url() == "/yellow")
      color = "red";
    if (request->url() == "/startup_time")
      setStartupTime(request->getParam("value")->value());
    if (request->url() == "/shutdown_time")
      setShutdownTime(request->getParam("value")->value());
    if (request->url() == "/manual_brightness")
      manual_brightness = (uint8_t)request->getParam("value")->value().toInt();
    if (request->url() == "/auto_brightness")
      auto_brightness = request->getParam("value")->value() == "ON";
    if (request->url() == "/reset")
      reset();

    request->send(SPIFFS, "/index.html", "text/html", false, getValue);
  }

private:
  void setShutdownTime(String a_str) {
    shutdownTime = Time::parseMinString(a_str);
    shutdown = !isDayTime(rtc.read());
  }

  void setStartupTime(String a_str) {
    startupTime = Time::parseMinString(a_str);
    shutdown = !isDayTime(rtc.read());
  }
  
  void reset() {
    shutdown = false;
    startupTime = Time();
    shutdownTime = Time();
    color = "white";
  }

private:
  static String getValue(const String& a_var) {
    if (a_var == "STATE")
      return shutdown ? "OFF" : "ON";
    if (a_var == "STARTUP_TIME")
      return startupTime.toMinString();
    if (a_var == "SHUTDOWN_TIME")
      return shutdownTime.toMinString();
    if (a_var == "MANUAL_BRIGHTNESS")
      return String((int)manual_brightness);
    if (a_var == "AUTO_BRIGHTNESS")
      return auto_brightness ? "checked" : "";
    return "INVALID";
  }
};