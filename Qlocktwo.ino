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
bool shutdown = false;
int brightness = 160;

// Own header files
#include "RTC.h"
#include "Display.h"
#include "Connecting.h"

RTC rtc(DS3231_I2C_ADDRESS);



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

void printWeekday(int dayOfWeek) {
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

void printStatus(Time a_time) {  
  Serial.print("Current-Time: ");
  Serial.println(toString(a_time));
  Serial.print("Startup-Time: ");
  Serial.println(startupTime + ".00");
  Serial.print("Shutdown-Time: ");
  Serial.println(shutdownTime + ".00");
  Serial.print("sliderValue:");
  Serial.println(sliderValue);
  printWeekday(a_time.weekday);
}

void setup() {
  Serial.begin(115200);
  timer.every(1000, onTimeout);
  connectWifi();
  updateRTC(rtc);
  setupServer();
  pixels.show();
}

void updateShutdown(Time a_time) {
  String currentTime = toString(a_time);
  if (currentTime == startupTime || currentTime == "0" + startupTime)
    shutdown = false;
  if (currentTime == shutdownTime || currentTime == "0" + shutdownTime)
    shutdown = true;
}

void onTimeout() {
  Time time = rtc.read();
  printStatus(time);
  updateBrightness();
  updateShutdown(time);
  displayTime(time);
  if (time.minute == 20 && time.second == 0)
    connectWifi();
  if (time.weekday == Sunday && time.hour == 5 && time.minute == 0 && time.second == 30)
    updateRTC(rtc);
}

void loop(){
  timer.update();
}
