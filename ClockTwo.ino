// TODO:
// - Reload website on startup/shutdown-time change
// - Persisted configuration-structure
// - Color-input & color-variable as uint32_t
// - High-German and Swabian version in same sketch
// - summer and winter Time
// - Redesign websites / push params without reloading website?
// - Update RTC on WiFi connect

#include <Timer.h>
#include "Timing.h"
#include "Display.h"
#include "Server.h"

#define PHOTORESISTOR_PIN 35

uint8_t getAutoBrightness() {
  int sensor = analogRead(PHOTORESISTOR_PIN);
  int limit = map(sensor, 0, 2500, 0, 100);
  if (sensor > 2500)
    limit = 100;

  static uint8_t value = 70;
  if (limit < value - 3)
    value -= 3;
  if (limit > value + 3)
    value += 3;
  if (limit < 10)
    value = 10;
  return value;
}

uint8_t getBrightness() {
  if (shutdown)
    return 0;
  if (config.autoBrightness())
    return getAutoBrightness();
  return 255;  
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid.c_str(), password.c_str());
  WiFi.setHostname("ClockTwo");
  setupServer();
  updateRTC();
  pixels.show();
}

bool updateNightTime(Time a_time) {
  if (a_time == config.shutdownTime())
    shutdown = true;
  if (a_time == config.startupTime())
    shutdown = false;
}

void onTimeout() {
  Time time = rtc.read();
  updateNightTime(time);

  uint32_t color = config.color().dimm(getBrightness()).toAdafruit();
  displayTime(time, color);

  if (WiFi.isConnected())
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
