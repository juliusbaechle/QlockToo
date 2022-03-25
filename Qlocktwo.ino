#include <Timer.h>
#include "RTC.h"
#include "NTP.h"
#include "Display.h"

// TODO:
// - Reload website on startup/shutdown-time change
// - Persisted configuration-structure
// - Color-input & color-variable as uint32_t
// - High-German and Swabian version in same sketch
// - summer and winter Time
// - Rename QlockTwo to ClockTwo

#define PHOTORESISTOR_PIN 35
#define DS3231_I2C_ADDRESS 0x68

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
  WiFi.begin(ssid.c_str(), password.c_str());
  setupServer();
  updateRTC();
  pixels.show();
}

void updateRTC() {
  static uint64_t updateRtcMs = 0;
  static bool initialized = false;

  if (initialized && millis() - updateRtcMs < 60 * 60 * 1000) return;
  if (!WiFi.isConnected()) return;
  initialized = true;

  Serial.print("RTC-Update: ");
  if (timeClient.update()) {
    Serial.println("succeeded");
    rtc.set(readTimeNTP());
    updateRtcMs = millis();
  } else {
    Serial.println("failed");
  }
}

void onTimeout() {
  Time time = rtc.read();
  updateNightTime(time);
  displayTime(time, getColor(getBrightness()));
  updateRTC();

  Serial.print("WiFi: ");
  Serial.println(WiFi.isConnected());
}



void loop(){
  dnsServer.processNextRequest();

  static uint64_t timeoutMs = 0;
  if (millis() - timeoutMs > 1000) {
    timeoutMs = millis();
    onTimeout();
  }

  static uint64_t disconnectedMs = 0;
  if (WiFi.isConnected())
    disconnectedMs = millis();
  setWiFiMode(millis() - disconnectedMs > 10 * 1000);
}
