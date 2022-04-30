#include "QlockServer.h"
#include "WebsiteHandler.h"
#include "AccessPointHandler.h"

#include <WiFi.h>
#include <AsyncTCP.h>

void QlockServer::initialize() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(m_qlock.wifiSsid().c_str(), m_qlock.wifiPassword().c_str());
  WiFi.setHostname(m_qlock.qlockName().c_str());
  WiFi.setAutoReconnect(false);
  WiFi.setSleep(false);

  m_server.addHandler(new WebsiteHandler(m_qlock)).setFilter(ON_STA_FILTER);
  m_server.addHandler(new AccessPointHandler(m_qlock)).setFilter(ON_AP_FILTER);
  m_server.begin();
}

void QlockServer::update() {
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

void QlockServer::enableAccessPoint(bool a_enabled) {
  if (m_accessPointEnabled == a_enabled) return;
  m_accessPointEnabled = a_enabled;

  if (m_accessPointEnabled) {
    Serial.println("enabled access point");
    WiFi.mode(WIFI_MODE_APSTA);
    WiFi.softAP(m_qlock.qlockName().c_str(), m_qlock.qlockPassword().c_str());
    m_dnsServer.start(53, "*", WiFi.softAPIP());
  } else {    
    Serial.println("disabled access point");
    WiFi.mode(WIFI_MODE_STA);
    m_dnsServer.stop();
  }
}
