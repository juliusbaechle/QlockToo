#include "QlockClock.h"
#include <Wire.h>
#include <WiFi.h>

#define DS3231_I2C_ADDRESS 0x68

inline byte decToHex(byte val) { return ((val / 10 * 16) + (val % 10)); }
inline byte hexToDec(byte val) { return ((val / 16 * 10) + (val % 16)); }

QlockClock::QlockClock() {
  Wire.begin();
}

void QlockClock::update() {
  if (!WiFi.isConnected()) return;
  if (millis() < m_nextUpdateMs) return;

  Serial.print("RTC-Update: ");
  if (m_timeClient.update()) {
    m_nextUpdateMs = millis() + 5 * 60 * 1000;
    setRTCTime(getNTPTime());
    Serial.println("succeeded");
  } else {
    Serial.println("failed");
  }
}

Time QlockClock::currentTime() {
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0);
  Wire.endTransmission();

  Time time;
  Wire.requestFrom(DS3231_I2C_ADDRESS, 3);
  time.second = hexToDec(Wire.read() & 0x7f);
  time.minute = hexToDec(Wire.read());
  time.hour = hexToDec(Wire.read() & 0x3f);
  return time;
}

Time QlockClock::getNTPTime() {
  Time time;
  time.hour = (uint8_t)m_timeClient.getHours();
  time.minute = (uint8_t)m_timeClient.getMinutes();
  time.second = (uint8_t)m_timeClient.getSeconds();
  return time;
}

void QlockClock::setRTCTime(Time a_time) {
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0);
  Wire.write(decToHex(a_time.second));
  Wire.write(decToHex(a_time.minute));
  Wire.write(decToHex(a_time.hour));
  Wire.endTransmission();
}
