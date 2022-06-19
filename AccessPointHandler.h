#ifndef ACCESS_POINT_HANDLER__H
#define ACCESS_POINT_HANDLER__H

#include <ESPAsyncWebServer.h>
#include "QlockToo.h"

class AccessPointHandler : public AsyncWebHandler {
public:
  AccessPointHandler(QlockToo& a_qlock);
  AsyncEventSource& eventSource() { return m_events; }

  bool canHandle(AsyncWebServerRequest *request) override { return request->url() != "/events"; }
  void handleRequest(AsyncWebServerRequest *request) override;

private:
  void onSubmit(AsyncWebServerRequest* a_request);

private:
  QlockToo& m_qlock;
  AsyncEventSource m_events;
};

#endif
