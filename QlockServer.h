#ifndef SERVER__H
#define SERVER__H

#include <DNSServer.h>
#include <ESPAsyncWebServer.h>
#include "QlockToo.h"
#include "WebsiteHandler.h"
#include "AccessPointHandler.h"

class QlockServer {
public:
  QlockServer(QlockToo& a_qlock);
  void initialize();
  void update();

private:
  void enableAccessPoint(bool a_enabled);

private:
  bool m_accessPointEnabled = true;
  uint64_t m_reconnectMs = 0;
  uint64_t m_disconnectMs = 0;
  DNSServer m_dnsServer;
  AsyncWebServer m_server { 80 };

  QlockToo& m_qlock;
  WebsiteHandler m_websiteHandler;
  AccessPointHandler m_accessPointHandler;
};

#endif
