#include <SPIFFS.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Timer.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);

Timer timer;

AsyncWebServer server(80);

// Benutzername und Passwort für Eingabseite
const char* http_username = "admin";
const char* http_password = "admin";

// Name und Passwort des WLAN's
const char* ssid = "AndroidAP";
const char* password = "Mi07022018kW";

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
String onOffState="ON";

// TODO: Remove these globals
String currentTime;
bool shutdown = false;
int brightness = 160;

// Own header files
#include "RTC.h"
#include "Display.h"
#include "Connecting.h"

void updateBrightness() {
  if (auto_brightness == "1") {
    int sensorValue = analogRead(35);
    Serial.print("PhotoResistor: ");
    Serial.println(sensorValue);

    int limit = map(sensorValue, 0, 2500, 0, 255);
    if (sensorValue > 2500)
      limit = 255;
    if (limit < brightness - 5)
      brightness = brightness - 5;
    if (limit > brightness + 5)
      brightness = brightness + 5;
    if (brightness < 30)
      brightness = 30;
  }

  if (auto_brightness == "0") {
    brightness = sliderValue.toInt();
  }

  Serial.print("brightness = "); //Ausgabe am Serial-Monitor: Das Wort „Sensorwert: „
  Serial.println(brightness);
}

void printDayOfWeek(int dayOfWeek) {
  switch (dayOfWeek) {
  case 0:
    Serial.println("Sunday");
    break;
  case 1:
    Serial.println("Monday");
    break;
  case 2:
    Serial.println("Tuesday");
    break;
  case 3:
    Serial.println("Wednesday");
    break;
  case 4:
    Serial.println("Thursday");
    break;
  case 5:
    Serial.println("Friday");
    break;
  case 6:
    Serial.println("Saturday");
    break;
  }
}

void printStatus(int hour, int minute, int second, int dayOfWeek) {
  String minuten;
  String stunden;
  String sekunden;

  if (minute < 10) {
    minuten = "0" + String(minute);
  } else {
    minuten = String(minute);
  }

  if (hour < 10) {
    stunden = "0" + String(hour);
  } else {
    stunden = String(hour);
  }

  if (second < 10) {
    sekunden = "0" + String(second);
  } else {
    sekunden = String(second);
  }

  currentTime = stunden + "." + minuten + "." + sekunden;
  Serial.print("Current-Time: ");
  Serial.println(currentTime);
  Serial.print("Startup-Time: ");
  Serial.println(startupTime + ".00");
  Serial.print("Shutdown-Time: ");
  Serial.println(shutdownTime + ".00");
  Serial.print("sliderValue:");
  Serial.println(sliderValue);
  printDayOfWeek(dayOfWeek);
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  timer.every(1000, onTimeout);
  connectWifi();
  updateRTC();
  setupServer();
  pixels.show();
}

void onTimeout() {
  byte second, minute, hour, dayOfWeek;  
  readDS3231time(&second, &minute, &hour, &dayOfWeek);
  printStatus(hour, minute, second, dayOfWeek);
  updateBrightness();
  displayTime(hour, minute, second);
  if (minute == 20 && second == 0)
    connectWifi();
  if (dayOfWeek == Sunday && hour == 5 && minute == 0 && second == 30)
    updateRTC();
}

void loop(){
  timer.update();
}
