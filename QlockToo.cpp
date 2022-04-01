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
  updateNightMode(time);

  Color color = m_config.color();
  color.dimm(getRelBrightnessPerc());

  if (m_special == "") {
    m_display.displayTime(time, color);
  } else {
    m_display.displaySpecial(m_special, color);
  }
}

void QlockToo::updateNightMode(Time a_time) {
  if (a_time == m_config.startupTime())
    m_active = true;
  if (a_time == m_config.shutdownTime())
    m_active = false;
}

void QlockToo::onNightTimeChanged() {
  Time time = m_clock.currentTime();
  time.addHours(m_config.utcOffset());

  if (startupTime() < shutdownTime()) { 
    m_active = startupTime() < time && time < shutdownTime(); // 07:00 - 16:00
  } else { 
    m_active = startupTime() < time || time < shutdownTime(); // 16:00 - 07:00
  }
}

uint8_t QlockToo::getAutoBrightness() {
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

uint8_t QlockToo::getRelBrightnessPerc() {
  if (!m_active)
    return 0;
  if (m_config.adaptiveLuminosity())
    return getAutoBrightness();
  return 100;
}

void QlockToo::setColor(Color a_color) {
  m_config.setColor(a_color); 
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

void QlockToo::setActive(bool a_active) {
  m_active = a_active; 
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
  onNightTimeChanged(); 
  updateDisplay(); 
}

void QlockToo::setShutdownTime(Time a_time) {
  m_config.setShutdownTime(a_time); 
  onNightTimeChanged(); 
  updateDisplay(); 
}
