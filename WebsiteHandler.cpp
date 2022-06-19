#include "WebsiteHandler.h"
#include <ArduinoJson.h>
#include <SPIFFS.h>

inline String toJsonArray(const std::vector<String> a_specials) {
  StaticJsonDocument<255> doc;
  JsonArray array = doc.to<JsonArray>();
  for (const String& special : a_specials)
    array.add(special);

  String str = "";
  serializeJson(doc, str);
  return str;
}

WebsiteHandler::WebsiteHandler(QlockToo& a_qlock)
  : m_qlock(a_qlock)
  , m_events("/events") 
{}

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

  String var = request->url();
  var.replace("/", "");
  String value = request->getParam("value")->value();

  Serial.print("variable: ");
  Serial.print(var);
  Serial.print(", value: ");
  Serial.println(value);

  setValue(var, value);
  m_events.send(value.c_str(), var.c_str(), millis());
  request->send(200);
}

void WebsiteHandler::setValue(const String& a_var, const String& a_value) {
  if (a_var == "auto_brightness")
    m_qlock.setAdaptiveLuminosity(a_value == "true");
  if (a_var == "foreground_color")
    m_qlock.setForegroundColor(Color::parse(a_value));
  if (a_var == "background_color")
    m_qlock.setBackgroundColor(Color::parse(a_value));
  if (a_var == "startup_time")
    m_qlock.setStartupTime(Time::parseMinString(a_value));
  if (a_var == "shutdown_time")
    m_qlock.setShutdownTime(Time::parseMinString(a_value));
  if (a_var == "utc_offset")
    m_qlock.setUtcOffset(a_value.toInt());
  if (a_var == "special")
    m_qlock.setSpecial(a_value);
}

String WebsiteHandler::getValue(const String& a_var) {
  if (a_var == "auto_brightness")
    return m_qlock.adaptiveLuminosity() ? "true" : "false";
  if (a_var == "foreground_color")
    return Color::toString(m_qlock.foregroundColor());
  if (a_var == "background_color")
    return Color::toString(m_qlock.backgroundColor());
  if (a_var == "startup_time")
    return Time::toMinString(m_qlock.startupTime());
  if (a_var == "shutdown_time")
    return Time::toMinString(m_qlock.shutdownTime());
  if (a_var == "utc_offset")
    return String(m_qlock.utcOffset());
  if (a_var == "possible_specials")
    return toJsonArray(m_qlock.possibleSpecials());
  if (a_var == "special")
    return m_qlock.special();
  return "invalid";
}
