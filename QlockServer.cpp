#include "QlockServer.h"
#include "WebsiteHandler.h"
#include "AccessPointHandler.h"

#include <WiFi.h>
#include <AsyncTCP.h>

void QlockServer::initialize(){
  WiFi.begin(m_qlock.wifiSsid().c_str(), m_qlock.wifiPassword().c_str());
  WiFi.setHostname("QlockToo");

  m_server.addHandler(new WebsiteHandler(m_qlock)).setFilter(ON_STA_FILTER);
  m_server.addHandler(new AccessPointHandler(m_qlock)).setFilter(ON_AP_FILTER);
  m_server.begin();
}

void QlockServer::update() {
  if(!m_connected)
    m_dnsServer.processNextRequest();

  if (WiFi.isConnected())
    m_disconnectMs = millis();
  setWifiMode(millis() - m_disconnectMs < 10 * 1000);
}

void QlockServer::setWifiMode(bool a_connected) {
  if (m_connected == a_connected) return;
  m_connected = a_connected;

  if (m_connected) {
    Serial.println("enabled station mode");
    WiFi.mode(WIFI_STA);
    m_dnsServer.stop();
  } else {
    Serial.println("enabled access point mode");
    WiFi.mode(WIFI_AP);
    WiFi.softAP("QlockToo", "QlockToo");
    m_dnsServer.start(53, "*", WiFi.softAPIP());
  }
}
