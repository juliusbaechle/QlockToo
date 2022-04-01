#ifndef WEBSITE_HANDLER__H
#define WEBSITE_HANDLER__H

#include <ESPAsyncWebServer.h>
#include "QlockToo.h"

class WebsiteHandler : public AsyncWebHandler {
public:
  WebsiteHandler(QlockToo& a_qlock) : m_qlock(a_qlock) {};
  virtual ~WebsiteHandler() {}

  bool canHandle(AsyncWebServerRequest *request) override { return true; }
  void handleRequest(AsyncWebServerRequest *request) override;

private:
  void handleGetRequest(AsyncWebServerRequest* request);
  void handlePutRequest(AsyncWebServerRequest* request);

private:
  String getValue(const String& a_var);

private:
  QlockToo& m_qlock;
};

#endif
