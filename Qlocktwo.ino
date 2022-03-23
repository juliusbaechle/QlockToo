#include <Timer.h>
#include "RTC.h"
#include "NTP.h"
#include "Display.h"

// TODO:
// - Reload server on startup/shutdown-time change
// - Persisted configuration-structure
// - Arduino as WiFi-Hotspot
// - More efficient logic for NTP updates and WiFi connects
// - Color-input & color-variable as uint32_t

#define PHOTORESISTOR_PIN 35
#define DS3231_I2C_ADDRESS 0x68

Timer timer;
RTC rtc(DS3231_I2C_ADDRESS);

#include "Server.h"

uint8_t getAutoBrightness() {
  int sensor = analogRead(PHOTORESISTOR_PIN);
  int limit = map(sensor, 0, 2500, 0, 255);
  if (sensor > 2500)
    limit = 255;

  static uint8_t value = 160;
  if (limit < value - 5)
    value -= 5;
  if (limit > value + 5)
    value += 5;
  if (limit < 30)
    value = 30;
  return value;
}

uint8_t getBrightness() {
  if (shutdown)
    return 0;
  if (auto_brightness)
    return getAutoBrightness();
  return manual_brightness;  
}

uint32_t getColor(uint8_t a_brightness) {
  if (color == "red")
    return Adafruit_NeoPixel::Color(0, a_brightness, 0, 0);
  if (color == "green")
    return Adafruit_NeoPixel::Color(a_brightness, 0, 0, 0);
  if (color == "blue")
    return Adafruit_NeoPixel::Color(0, 0, a_brightness, 0);
  if (color == "purple")
    return Adafruit_NeoPixel::Color(153, 50, 204, 0);
  if (color == "yellow")
    return Adafruit_NeoPixel::Color(a_brightness, a_brightness, 0, 0);
  return Adafruit_NeoPixel::Color(0, 0, 0, a_brightness);
}

void setup() {
  Serial.begin(115200);
  timer.every(1000, onTimeout);
  connectWiFi();
  updateRTC(rtc);
  setupServer();
  pixels.show();
}

void onTimeout() {
  Time time = rtc.read();
  updateNightTime(time);
  displayTime(time, getColor(getBrightness()));
  if (time.minute == 20 && time.second == 0)
    connectWiFi();
  if (time.hour == 5 && time.minute == 0 && time.second == 30)
    updateRTC(rtc);
}

void loop(){
  timer.update();
}
