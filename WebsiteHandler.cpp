#include "WebsiteHandler.h"
#include <ArduinoJson.h>
#include <SPIFFS.h>

void WebsiteHandler::handleRequest(AsyncWebServerRequest *request) {
  Serial.print("request on sta: ");
  Serial.println(request->url());

  if (request->method() == HTTP_GET)
    handleGetRequest(request);

  if (request->method() == HTTP_PUT)
    handlePutRequest(request);
}

void WebsiteHandler::handleGetRequest(AsyncWebServerRequest* request) {
  if (!request->authenticate(m_qlock.qlockName().c_str(), m_qlock.qlockPassword().c_str()))
    return request->requestAuthentication();
    
  if (request->url() == "/")
    return request->send(SPIFFS, "/index.html", "text/html", false, [this](String str) { return getValue(str); });
  if (request->url() == "/index.js")
    return request->send(SPIFFS, "/index.js", "text/javascript", false, [this](String str) { return getValue(str); });
  if (request->url() == "/index.css")
    return request->send(SPIFFS, "/index.css", "text/css");
  if (request->url() == "/icon.png")
    return request->send(SPIFFS, "/icon.png", "image/png");
  request->send(404);
}

void WebsiteHandler::handlePutRequest(AsyncWebServerRequest* request) {
  if (!request->authenticate(m_qlock.qlockName().c_str(), m_qlock.qlockPassword().c_str()))
    return request->requestAuthentication();

  Serial.print("value: ");
  Serial.println(request->getParam("value")->value());

  if (request->url() == "/foreground_color")
    m_qlock.setForegroundColor(Color::parse(request->getParam("value")->value()));
  if (request->url() == "/background_color")
    m_qlock.setBackgroundColor(Color::parse(request->getParam("value")->value()));
  if (request->url() == "/startup_time")
    m_qlock.setStartupTime(Time::parseMinString(request->getParam("value")->value()));
  if (request->url() == "/shutdown_time")
    m_qlock.setShutdownTime(Time::parseMinString(request->getParam("value")->value()));
  if (request->url() == "/auto_brightness")
    m_qlock.setAdaptiveLuminosity(request->getParam("value")->value() == "true");
  if (request->url() == "/utc_offset")
    m_qlock.setUtcOffset(request->getParam("value")->value().toInt());
  if (request->url() == "/special")
    m_qlock.setSpecial(request->getParam("value")->value());

  request->send(200);
}

inline String toJsonArray(const std::vector<String> a_specials) {
  StaticJsonDocument<255> doc;
  JsonArray array = doc.to<JsonArray>();
  for (const String& special : a_specials)
    array.add(special);

  String str = "";
  serializeJson(doc, str);
  return str;
}

String WebsiteHandler::getValue(const String& a_var) {
  if (a_var == "AUTO_BRIGHTNESS")
    return m_qlock.adaptiveLuminosity() ? "checked" : "";
  if (a_var == "FOREGROUND_COLOR")
    return Color::toString(m_qlock.foregroundColor());
  if (a_var == "BACKGROUND_COLOR")
    return Color::toString(m_qlock.backgroundColor());
  if (a_var == "STARTUP_TIME")
    return Time::toMinString(m_qlock.startupTime());
  if (a_var == "SHUTDOWN_TIME")
    return Time::toMinString(m_qlock.shutdownTime());
  if (a_var == "UTC_OFFSET")
    return String(m_qlock.utcOffset());
  if (a_var == "POSSIBLE_SPECIALS")
    return toJsonArray(m_qlock.possibleSpecials());
  return "INVALID";
}
