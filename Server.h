#pragma once

#include <SPIFFS.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);

// Benutzername und Passwort f�r Eingabseite
const char* http_username = "admin";
const char* http_password = "admin";

// Parameter-Identifiers in Website
const char* PARAM_STARTUP_TIME = "input1";
const char* PARAM_SHUTDOWN_TIME = "input2";
const char* PARAM_SLIDER_VALUE = "value";
const char* PARAM_AUTO_BRIGHTNESS = "state";

// Config set by Server
String sliderValue = "255";
String color = "rot";
String startupTime = "-";
String shutdownTime = "-";
String auto_brightness = "1";
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
  if(var == "GPIO_STATE")
    return shutdown ? "OFF" : "ON";
  if(var == "An_STATE")     
    return startupTime;
  if(var == "Aus_STATE")    
    return shutdownTime;
  if(var == "SLIDERVALUE") 
    return sliderValue;
  return shutdown ? "OFF" : "ON", startupTime, sliderValue;
}

void setupServer() {
  if (!SPIFFS.begin(true))
    Serial.println("An Error has occurred while mounting SPIFFS");
  
  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    if(!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    request->send(SPIFFS, "/index.html", String(), false, getValue);
  });
  
  // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("requested /style.css");
    if(!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    request->send(SPIFFS, "/style.css", "text/css");
  });

  server.on("/led2on", HTTP_GET, [](AsyncWebServerRequest *request){
    if(!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    shutdown = false;
    request->send(SPIFFS, "/index.html", String(), false, getValue);
  });

  server.on("/led2off", HTTP_GET, [](AsyncWebServerRequest *request){
    if(!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    shutdown = true;
    request->send(SPIFFS, "/index.html", String(), false, getValue);
  });

  server.on("/white", HTTP_GET, [](AsyncWebServerRequest *request){
    if(!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    color="weis";  
    shutdown = false;
    request->send(SPIFFS, "/index.html", String(), false, getValue);
  });
  
  server.on("/red", HTTP_GET, [](AsyncWebServerRequest *request){
    if(!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    color="rot"; 
    shutdown = false;
    request->send(SPIFFS, "/index.html", String(), false, getValue);
  });

  server.on("/gr�n", HTTP_GET, [](AsyncWebServerRequest *request){
    if(!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    color="gr�n"; 
    shutdown = false;
    request->send(SPIFFS, "/index.html", String(), false, getValue);
  });

  server.on("/blau", HTTP_GET, [](AsyncWebServerRequest *request){
    if(!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    color="blau"; 
    shutdown = false;
    request->send(SPIFFS, "/index.html", String(), false, getValue);
  });
  
  server.on("/violett", HTTP_GET, [](AsyncWebServerRequest *request){
    if(!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    color="violett";
    shutdown = false;
    request->send(SPIFFS, "/index.html", String(), false, getValue);
  });
  
  server.on("/gelb", HTTP_GET, [](AsyncWebServerRequest *request){
    if(!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    color="gelb"; 
    shutdown = false;
    request->send(SPIFFS, "/index.html", String(), false, getValue);
  });

  // Send a GET request to <ESP_IP>/get?input1=<inputMessage>
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    Serial.println("requested /get");
    if(!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
   
    // GET input1 value on <ESP_IP>/get?input1=<inputMessage>
    if (request->hasParam(PARAM_STARTUP_TIME)) {
      startupTime = request->getParam(PARAM_STARTUP_TIME)->value();
    }

    // GET input2 value on <ESP_IP>/get?input2=<inputMessage>
    if (request->hasParam(PARAM_SHUTDOWN_TIME)) {
      shutdownTime = request->getParam(PARAM_SHUTDOWN_TIME)->value();
    } else {
      startupTime = "No message sent";
    }

    server.on("/button9", HTTP_GET, [](AsyncWebServerRequest *request){
      if(!request->authenticate(http_username, http_password))
        return request->requestAuthentication();
      shutdown = false;
      startupTime="Reset";
      shutdownTime="Reset";
      pixels.clear();
      request->send(SPIFFS, "/index.html", String(), false, getValue);
    });

    request->send(SPIFFS, "/index.html", String(), false, getValue);
  }); 

  server.on("/slider", HTTP_GET, [] (AsyncWebServerRequest *request) {
    // GET input1 value on <ESP_IP>/slider?value=<inputMessage>
    if(!request->authenticate(http_username, http_password))
      return request->requestAuthentication();

    String inputMessage;
    if (request->hasParam(PARAM_SLIDER_VALUE)) {
      inputMessage = request->getParam(PARAM_SLIDER_VALUE)->value();
      sliderValue = inputMessage;
    }
    request->send(SPIFFS, "/index.html", String(), false, getValue);
  });

  server.on("/update", HTTP_GET, [] (AsyncWebServerRequest *request) {
    Serial.println("requested /update");
    // GET input1 value on <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
    if (request->hasParam(PARAM_AUTO_BRIGHTNESS))
      auto_brightness = request->getParam(PARAM_AUTO_BRIGHTNESS)->value();
    else
      auto_brightness= "No message sent";
    Serial.print("GPIO: ");
    Serial.println(auto_brightness);

    request->send(SPIFFS, "/index.html", String(), false, getValue);
  });

  server.on("/logout", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("requested /logout");
    request->send(401);
  });

  server.on("/logged-out", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", logout_html, getValue);
  });

  // Start server
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
