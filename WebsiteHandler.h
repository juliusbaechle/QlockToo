#ifndef WEBSITE_HANDLER__H
#define WEBSITE_HANDLER__H

#include <ESPAsyncWebServer.h>
#include "QlockToo.h"

class WebsiteHandler : public AsyncWebHandler {
public:
  WebsiteHandler(QlockToo& a_qlock);
  AsyncEventSource& eventSource() { return m_events; }

  bool canHandle(AsyncWebServerRequest *request) override { return request->url() != "/events"; }
  void handleRequest(AsyncWebServerRequest *request) override;

private:
  void handleGetRequest(AsyncWebServerRequest* request);
  void handlePutRequest(AsyncWebServerRequest* request);

  void setValue(const String& a_varName, const String& a_value);
  String getValue(const String& a_var);

private:
  QlockToo& m_qlock;
  AsyncEventSource m_events;
};

#endif
