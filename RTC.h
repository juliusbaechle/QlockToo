#pragma once

#include <Wire.h>
#include "Time.h"

class RTC {
public:
  RTC(uint16_t a_i2cAdress) {
    Wire.begin();
    m_i2cAdress = a_i2cAdress;
  }

  void set(Time a_time) {
    Wire.beginTransmission(m_i2cAdress);
    Wire.write(0);
    Wire.write(decToHex(a_time.second));
    Wire.write(decToHex(a_time.minute));
    Wire.write(decToHex(a_time.hour));
    Wire.endTransmission();
  }

  Time read() const {
    Wire.beginTransmission(m_i2cAdress);
    Wire.write(0);
    Wire.endTransmission();

    Time time;
    Wire.requestFrom(m_i2cAdress, 4);
    time.second = hexToDec(Wire.read() & 0x7f);
    time.minute = hexToDec(Wire.read());
    time.hour = hexToDec(Wire.read() & 0x3f);
    return time;
  }

private:
  inline static byte decToHex(byte val) {
    return ((val / 10 * 16) + (val % 10));
  }

  inline static byte hexToDec(byte val) {
    return ((val / 16 * 10) + (val % 16));
  }

private:
  int m_i2cAdress = 0;
};