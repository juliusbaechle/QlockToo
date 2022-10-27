#include "QlockTooServer.h"

#include <WiFi.h>
#include <AsyncTCP.h>

QlockTooServer::QlockTooServer(QlockToo& a_qlock)
  : m_qlock(a_qlock)
  , m_websiteHandler(a_qlock)
  , m_accessPointHandler(a_qlock)
{}

void QlockTooServer::initialize() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(m_qlock.wifiSsid().c_str(), m_qlock.wifiPassword().c_str());
  WiFi.setHostname(m_qlock.name().c_str());
  WiFi.setAutoReconnect(false);
  WiFi.setSleep(false);

  m_server.addHandler(&m_websiteHandler).setFilter(ON_STA_FILTER);
  m_server.addHandler(&m_websiteHandler.eventSource()).setFilter(ON_STA_FILTER);
  m_server.addHandler(&m_accessPointHandler).setFilter(ON_AP_FILTER);
  m_server.addHandler(&m_accessPointHandler.eventSource()).setFilter(ON_AP_FILTER);
  m_server.begin();
}

void QlockTooServer::update() {
  if(m_accessPointEnabled)
    m_dnsServer.processNextRequest();

  if (millis() - m_reconnectMs > 5 * 1000) {
    m_reconnectMs = millis();
    Serial.print("WiFi: ");
    Serial.println(WiFi.isConnected());
    if(!WiFi.isConnected())
      WiFi.reconnect();
  }

  if (WiFi.isConnected())
    m_disconnectMs = millis();
  bool accessPointEnabled = millis() - m_disconnectMs > 10 * 1000;
  accessPointEnabled &= !m_qlock.isInNightMode();
  enableAccessPoint(accessPointEnabled);
}

void QlockTooServer::enableAccessPoint(bool a_enabled) {
  if (m_accessPointEnabled == a_enabled) return;
  m_accessPointEnabled = a_enabled;

  if (m_accessPointEnabled) {
    Serial.println("enabled access point");
    WiFi.mode(WIFI_MODE_APSTA);
    WiFi.softAP(m_qlock.name().c_str(), m_qlock.password().c_str());
    m_dnsServer.start(53, "*", WiFi.softAPIP());
  } else {
    Serial.println("disabled access point");
    WiFi.mode(WIFI_MODE_STA);
    m_dnsServer.stop();
  }
}
