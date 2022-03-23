#pragma once

#include <SPIFFS.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);

// Benutzername und Passwort f�r Eingabseite
const char* http_username = "admin";
const char* http_password = "admin";

// Config set by Server
String color = "rot";
Time startupTime;
Time shutdownTime;
bool auto_brightness = true;
uint8_t manual_brightness = 255;
bool shutdown = false;

//Website nach Bet�tigung des Logouts
const char logout_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
</head>
<body>
  <p>Logged out or <a href="/">return to homepage</a>.</p>
  <p><strong>Note:</strong> close all web browser tabs to complete the logout process.</p>
</body>
</html>
)rawliteral";

// Replaces placeholder with LED state /Slidervalue value
String getValue(const String& var) {
  if(var == "STATE")
    return shutdown ? "OFF" : "ON";
  if (var == "STARTUP_TIME")
    return startupTime.toMinString();
  if (var == "SHUTDOWN_TIME")
    return shutdownTime.toMinString();
  if(var == "MANUAL_BRIGHTNESS") 
    return String((int) manual_brightness);
  if (var == "AUTO_BRIGHTNESS")
    return auto_brightness ? "checked" : "";
  return "INVALID";
}

bool isDayTime(Time a_time) {
  if (startupTime < shutdownTime) {
    return startupTime < a_time && a_time < shutdownTime;
  } else {
    return startupTime < a_time || a_time < shutdownTime;
  }
}

bool updateNightTime(Time a_time) {
  if (a_time == shutdownTime)
    shutdown = true;
  if (a_time == startupTime)
    shutdown = false;
}

void setupServer() {
  if (!SPIFFS.begin(true))
    Serial.println("An Error has occurred while mounting SPIFFS");
  
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    if(!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    request->send(SPIFFS, "/index.html", String(), false, getValue);
  });

  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/style.css", "text/css");
  });

  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request) {
    shutdown = false;
    request->send(SPIFFS, "/index.html", String(), false, getValue);
  });

  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request) {
    shutdown = true;
    request->send(SPIFFS, "/index.html", String(), false, getValue);
  });

  server.on("/white", HTTP_GET, [](AsyncWebServerRequest *request) {
    color="white";  
    shutdown = false;
    request->send(SPIFFS, "/index.html", String(), false, getValue);
  });
  
  server.on("/red", HTTP_GET, [](AsyncWebServerRequest *request) {
    color="red"; 
    shutdown = false;
    request->send(SPIFFS, "/index.html", String(), false, getValue);
  });

  server.on("/green", HTTP_GET, [](AsyncWebServerRequest *request) {
    color="green"; 
    shutdown = false;
    request->send(SPIFFS, "/index.html", String(), false, getValue);
  });

  server.on("/blue", HTTP_GET, [](AsyncWebServerRequest *request) {
    color="blue"; 
    shutdown = false;
    request->send(SPIFFS, "/index.html", String(), false, getValue);
  });
  
  server.on("/purple", HTTP_GET, [](AsyncWebServerRequest *request) {
    color="purple";
    shutdown = false;
    request->send(SPIFFS, "/index.html", String(), false, getValue);
  });
  
  server.on("/yellow", HTTP_GET, [](AsyncWebServerRequest *request) {
    color="yellow"; 
    shutdown = false;
    request->send(SPIFFS, "/index.html", String(), false, getValue);
  });

  server.on("/startup_time", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (request->hasParam("value")) {
      String time = request->getParam("value")->value();
      startupTime = Time::parseMinString(time);
      shutdown = !isDayTime(rtc.read());
    }    
    request->send(SPIFFS, "/index.html", String(), false, getValue);
  });

  server.on("/shutdown_time", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (request->hasParam("value")) {
      String time = request->getParam("value")->value();
      shutdownTime = Time::parseMinString(time);
      shutdown = !isDayTime(rtc.read());
    }
    request->send(SPIFFS, "/index.html", String(), false, getValue);
  });

  server.on("/reset", HTTP_GET, [](AsyncWebServerRequest *request) {
    shutdown = false;
    startupTime = Time();
    shutdownTime = Time();
    color = "white";
    request->send(SPIFFS, "/index.html", String(), false, getValue);
  });

  server.on("/manual_brightness", HTTP_GET, [] (AsyncWebServerRequest *request) {
    if (request->hasParam("value"))
      manual_brightness = (uint8_t) request->getParam("value")->value().toInt();
    request->send(SPIFFS, "/index.html", String(), false, getValue);
  });

  server.on("/auto_brightness", HTTP_GET, [] (AsyncWebServerRequest *request) {
    if (request->hasParam("value"))
      auto_brightness = request->getParam("value")->value() == "ON";
    request->send(SPIFFS, "/index.html", String(), false, getValue);
  });

  server.on("/logout", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("requested /logout");
    request->send(401);
  });

  server.on("/logged-out", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", logout_html, getValue);
  });

  server.begin();
}


#include <WiFi.h>

// Name und Passwort des WLAN's
const char* ssid = "FRITZ! Box 7412 Repeater";
const char* password = "54658123531998163263";

bool connectWiFi() {
  WiFi.begin(ssid, password);

  Serial.print("connecting ");
  for (int attempt = 0; attempt < 10 && WiFi.status() != WL_CONNECTED; attempt++) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("connected wifi, IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("failed to connect wifi");
  }
  
  return WiFi.status() == WL_CONNECTED;
}
