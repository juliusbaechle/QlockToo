#pragma once


//Website nach Betätigung des Logouts
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
    return onOffState;
  if(var == "An_STATE")     
    return startupTime;
  if(var == "Aus_STATE")    
    return shutdownTime;
  if(var == "SLIDERVALUE") 
    return sliderValue;
  return onOffState, startupTime, shutdownTime;
}

void setupServer() {
  // Initialize SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    if(!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    request->send(SPIFFS, "/index.html", String(), false, getValue);
  });
  
  // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    if(!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    request->send(SPIFFS, "/style.css", "text/css");
  });

  server.on("/led2on", HTTP_GET, [](AsyncWebServerRequest *request){
    if(!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    onOffState="ON";
    shutdown="ON"; 
    request->send(SPIFFS, "/index.html", String(), false, getValue);
  });

  server.on("/led2off", HTTP_GET, [](AsyncWebServerRequest *request){
    if(!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    onOffState="OFF";  
    request->send(SPIFFS, "/index.html", String(), false, getValue);
  });

  server.on("/white", HTTP_GET, [](AsyncWebServerRequest *request){
    if(!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    color="weis";  
    onOffState="ON";
    shutdown="ON"; 
    request->send(SPIFFS, "/index.html", String(), false, getValue);
  });
  
  server.on("/red", HTTP_GET, [](AsyncWebServerRequest *request){
    if(!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    color="rot"; 
    onOffState="ON"; 
    shutdown="ON"; 
    request->send(SPIFFS, "/index.html", String(), false, getValue);
  });

  server.on("/grün", HTTP_GET, [](AsyncWebServerRequest *request){
    if(!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    color="grün"; 
    onOffState="ON"; 
    request->send(SPIFFS, "/index.html", String(), false, getValue);
  });

  server.on("/blau", HTTP_GET, [](AsyncWebServerRequest *request){
    if(!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    color="blau"; 
    onOffState="ON"; 
    shutdown="ON"; 
    request->send(SPIFFS, "/index.html", String(), false, getValue);
  });
  
  server.on("/violett", HTTP_GET, [](AsyncWebServerRequest *request){
    if(!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    color="violett";
    onOffState="ON";  
    request->send(SPIFFS, "/index.html", String(), false, getValue);
  });
  
  server.on("/gelb", HTTP_GET, [](AsyncWebServerRequest *request){
    if(!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    color="gelb"; 
    onOffState="ON"; 
    shutdown="ON"; 
    request->send(SPIFFS, "/index.html", String(), false, getValue);
  });

  // Send a GET request to <ESP_IP>/get?input1=<inputMessage>
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
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
      shutdown="ON";
      onOffState="ON";
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
    request->send(401);
  });

  server.on("/logged-out", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", logout_html, getValue);
  });

  // Start server
  server.begin();
}

bool connectWifi() {
  static int connectionAttempts;
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    connectionAttempts = ++connectionAttempts;
    delay(500);
    Serial.print(".");
    Serial.print(connectionAttempts);
    if (connectionAttempts == 15) {
      connectionAttempts = 0;
      return false;
    }
    if (WiFi.status() == WL_CONNECTED) {
      connectionAttempts = 0;
      Serial.print("Connected, IP: ");
      Serial.println(WiFi.localIP());
    }
  }
  return true;
}

Time readTimeNTP() {
  Time time;
  time.hour = (uint8_t)timeClient.getHours();
  time.minute = (uint8_t)timeClient.getMinutes();
  time.second = (uint8_t)timeClient.getSeconds();
  time.weekday = (Weekday)timeClient.getDay();
  return time;
}

void updateRTC(RTC& rtc) {
  if (!timeClient.update()) return;
  rtc.set(readTimeNTP());
  Serial.print("sucessfully read time from ntp server");
}
