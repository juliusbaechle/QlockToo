#include "AccessPointHandler.h"
#include <SPIFFS.h>
#include <WiFi.h>

AccessPointHandler::AccessPointHandler(QlockToo& a_qlock)
  : m_qlock(a_qlock)
  , m_events("/events") 
{
  m_events.onConnect([&](AsyncEventSourceClient* client) {
    m_events.send("ping", NULL, millis(), 1000);
  });
}

void AccessPointHandler::handleRequest(AsyncWebServerRequest *request) {
  Serial.print("request on ap: ");
  Serial.println(request->url());

  if (request->url() == "/submit") {
    onSubmit(request);    
    return request->send(SPIFFS, "/credentials.html", "text/html");
  }

  if (request->url() == "/ping")
    return request->send(200);

  if (request->url() == "/credentials.css")
    return request->send(SPIFFS, "/credentials.css", "text/css");
  if (request->url() == "/credentials.js")
    return request->send(SPIFFS, "/credentials.js", "text/javascript");
  if (request->url() == "/icon.png")
    return request->send(SPIFFS, "/icon.png", "image/png");
  if (request->url() == "/eye.png")
    return request->send(SPIFFS, "/eye.png", "image/png");
  if (request->url() == "/eye_slash.png")
    return request->send(SPIFFS, "/eye_slash.png", "image/png");
  return request->send(SPIFFS, "/credentials.html", "text/html");
}

void AccessPointHandler::onSubmit(AsyncWebServerRequest* a_request) {
  if (a_request->hasParam("ssid"))
    m_qlock.setWifiSsid(a_request->getParam("ssid")->value());
  if (a_request->hasParam("password"))
    m_qlock.setWifiPassword(a_request->getParam("password")->value());
  WiFi.begin(m_qlock.wifiSsid().c_str(), m_qlock.wifiPassword().c_str());
}