#include "QlockServer.h"
#include "WebsiteHandler.h"
#include "AccessPointHandler.h"

#include <WiFi.h>
#include <AsyncTCP.h>

void QlockServer::initialize(){
  WiFi.begin(m_qlock.wifiSsid().c_str(), m_qlock.wifiPassword().c_str());
  WiFi.setHostname(m_qlock.qlockName().c_str());
  WiFi.setAutoReconnect(false);

  m_server.addHandler(new WebsiteHandler(m_qlock)).setFilter(ON_STA_FILTER);
  m_server.addHandler(new AccessPointHandler(m_qlock)).setFilter(ON_AP_FILTER);
  m_server.begin();
}

void QlockServer::update() {
  if(!m_connected)
    m_dnsServer.processNextRequest();

  if (millis() - m_reconnectMs > 5 * 1000) {
    if(!WiFi.isConnected())
      WiFi.reconnect();
    m_reconnectMs = millis();
  }    

  if (WiFi.isConnected())
    m_disconnectMs = millis();
  setWifiMode(millis() - m_disconnectMs < 10 * 1000);
}

void QlockServer::setWifiMode(bool a_connected) {
  if (m_connected == a_connected) return;
  m_connected = a_connected;

  if (m_connected) {
    Serial.println("disabled access point");
    WiFi.mode(WIFI_MODE_STA);
    m_dnsServer.stop();
  } else {
    Serial.println("enabled access point");
    WiFi.mode(WIFI_MODE_APSTA);
    WiFi.softAP(m_qlock.qlockName().c_str(), m_qlock.qlockPassword().c_str());
    m_dnsServer.start(53, "*", WiFi.softAPIP());
  }
}
