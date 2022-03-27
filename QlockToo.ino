// TODO:
// - Persisted configuration-structure
// - Push params from website without reload
// - Enhanced website stylesheets
// - Refactor/Simplify code

#include "Timing.h"
#include "Server.h"
#include "GermanDisplay.h"

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
  return 100;
}

void setup() {
  Serial.begin(115200);
  SPIFFS.begin(true);
  config = Configuration::load();
  WiFi.begin(config.wiFiSsid().c_str(), config.wiFiPassword().c_str());
  WiFi.setHostname("QlockToo");
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

void update() {
  Time time = rtc.read();
  time.addHours(config.utcOffset());
  updateNightTime(time);

  uint32_t color = config.color().dimm(getBrightness()).toInt();
  displayTime(time, color);

  if (WiFi.isConnected())
    updateRTC();

  Serial.print("WiFi: ");
  Serial.println(WiFi.isConnected());
}

void loop() {
  dnsServer.processNextRequest();

  static uint64_t timeoutMs = 0;
  if (millis() - timeoutMs > 1000) {
    timeoutMs = millis();
    update();
  }

  static uint64_t disconnectedMs = 0;
  if (WiFi.isConnected())
    disconnectedMs = millis();
  setWiFiMode(millis() - disconnectedMs > 10 * 1000);
}
