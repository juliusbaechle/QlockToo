#ifndef ACCESS_POINT_HANDLER__H
#define ACCESS_POINT_HANDLER__H

#include <ESPAsyncWebServer.h>
#include "QlockToo.h"

class AccessPointHandler : public AsyncWebHandler {
public:
  AccessPointHandler(QlockToo& a_qlock) : m_qlock(a_qlock) {}
  virtual ~AccessPointHandler() {}

  bool canHandle(AsyncWebServerRequest *request) override { return true; }
  void handleRequest(AsyncWebServerRequest *request) override;

private:
  void onSubmit(AsyncWebServerRequest* a_request);

private:
  QlockToo& m_qlock;
};

#endif
