#include "QlockToo.h"
#include "GermanDisplay.h"
#include <WiFi.h>

#define PHOTORESISTOR_PIN 35

void QlockToo::initialize() {
  m_config = Configuration::load();
}

void QlockToo::update() {
  m_clock.update();

  if (millis() > m_nextDisplayUpdateMs) {
    m_nextDisplayUpdateMs = millis() + 900;
    updateDisplay();
  }
}

void QlockToo::updateDisplay() {
  Serial.print("WiFi: ");
  Serial.println(WiFi.isConnected());

  Time time = m_clock.currentTime();
  time.addHours(m_config.utcOffset());

  int brightness = isNightTime(time) ? 0 : getBrightness();
  Color foreground = foregroundColor().dimm(brightness);
  Color background = backgroundColor().dimm(brightness);

  if (m_special == "") {
    m_display.displayTime(time, foreground, background);
  } else {
    m_display.displaySpecial(m_special, foreground, background);
  }
}

bool QlockToo::isNightTime(Time a_time) {
  if (startupTime() <= shutdownTime()) {
    return (shutdownTime() <= a_time) || (a_time <= startupTime()); // 23:00 - 07:00
  } else {
    return (shutdownTime() <= a_time) && (a_time <= startupTime()); // 07:00 - 23:00
  }
}

uint8_t QlockToo::getBrightness() {
  if (!m_config.adaptiveLuminosity())
    return 100;

  int sensor = analogRead(PHOTORESISTOR_PIN);
  int limit = map(sensor, 0, 2500, 0, 100);
  if (sensor > 2500)
    limit = 100;

  static uint8_t value = 70;
  if (limit < value - 3)
    value -= 3;
  if (limit > value + 3)
    value += 3;
  if (value < 10)
    value = 10;
  return value;
}

void QlockToo::setForegroundColor(Color a_color) {
  m_config.setForegroundColor(a_color);
  updateDisplay(); 
}

void QlockToo::setBackgroundColor(Color a_color) {
  m_config.setBackgroundColor(a_color);
  updateDisplay();
}

void QlockToo::setAdaptiveLuminosity(bool a_autoBrightness) {
  m_config.setAdaptiveLuminosity(a_autoBrightness); 
  updateDisplay(); 
}

void QlockToo::setUtcOffset(int8_t a_offset) {
  m_config.setUtcOffset(a_offset); 
  updateDisplay(); 
}

void QlockToo::setSpecial(const String& a_special) {
  if (a_special == "")
    m_special = "";

  auto specials = m_display.possibleSpecials();
  if (std::find(specials.begin(), specials.end(), a_special) != specials.end())
    m_special = a_special;

  updateDisplay();
}

void QlockToo::setStartupTime(Time a_time) {
  m_config.setStartupTime(a_time); 
  updateDisplay(); 
}

void QlockToo::setShutdownTime(Time a_time) {
  m_config.setShutdownTime(a_time); 
  updateDisplay(); 
}
