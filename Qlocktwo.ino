#include <Timer.h>
#include "RTC.h"
#include "NTP.h"
#include "Display.h"
#include "Server.h"

#define PHOTORESISTOR_PIN 35
#define DS3231_I2C_ADDRESS 0x68

Timer timer;
RTC rtc(DS3231_I2C_ADDRESS);

void updateNightMode(Time a_time) {
  String currentTime = toString(a_time);
  if (currentTime == startupTime || currentTime == "0" + startupTime)
    shutdown = false;
  if (currentTime == shutdownTime || currentTime == "0" + shutdownTime)
    shutdown = true;
}

uint8_t getBrightness() {
  if (shutdown)
    return 0;

  if (auto_brightness == "0")
    return (uint8_t) sliderValue.toInt();

  if (auto_brightness == "1") {
    static uint8_t value = 160;

    int sensorValue = analogRead(PHOTORESISTOR_PIN);
    Serial.print("PhotoResistor: ");
    Serial.println(sensorValue);

    int currentLimit = map(sensorValue, 0, 2500, 0, 255);
    if (currentLimit > 2500)
      value = 255;
    if (value < value - 5)
      value -= 5;
    if (value > value + 5)
      value += 5;
    if (value < 30)
      value = 30;
    return value;
  }
}

uint32_t getColor(uint8_t a_brightness) {
  if (color == "rot")
    return Adafruit_NeoPixel::Color(0, a_brightness, 0, 0);
  if (color == "grün")
    return Adafruit_NeoPixel::Color(a_brightness, 0, 0, 0);
  if (color == "blau")
    return Adafruit_NeoPixel::Color(0, 0, a_brightness, 0);
  if (color == "violett")
    return Adafruit_NeoPixel::Color(153, 50, 204, 0);
  if (color == "gelb")
    return Adafruit_NeoPixel::Color(a_brightness, a_brightness, 0, 0);
  return Adafruit_NeoPixel::Color(0, 0, 0, a_brightness);
}

void printStatus(Time a_time) {  
  Serial.print("Current-Time: ");
  Serial.println(toString(a_time));
  Serial.print("Startup-Time: ");
  Serial.println(startupTime);
  Serial.print("Shutdown-Time: ");
  Serial.println(shutdownTime);
  Serial.print("Slider-Brightness: ");
  Serial.println(sliderValue);
  Serial.print("Weekday: ");
  Serial.println(toString(a_time.weekday));
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
  // printStatus(time);
  updateNightMode(time);
  displayTime(time, getColor(getBrightness()));
  if (time.minute == 20 && time.second == 0)
    connectWiFi();
  if (time.weekday == Sunday && time.hour == 5 && time.minute == 0 && time.second == 30)
    updateRTC(rtc);
}

void loop(){
  timer.update();
}
