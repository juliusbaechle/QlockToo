#pragma once

#include <Wire.h>
#define DS3231_I2C_ADDRESS 0x68 //Adresse zur Kommunikation mit RTC

enum Weekday {
  Sunday,
  Monday,
  Tuesday,
  Wednesday,
  Thursday,
  Friday,
  Saturday
};

struct Time {
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
  Weekday weekday;
};

String toString(Time a_time) {
  String minuten;
  if (a_time.minute < 10) {
    minuten = "0" + String(a_time.minute);
  } else {
    minuten = String(a_time.minute);
  }

  String stunden;
  if (a_time.hour < 10) {
    stunden = "0" + String(a_time.hour);
  } else {
    stunden = String(a_time.hour);
  }

  String sekunden;
  if (a_time.second < 10) {
    sekunden = "0" + String(a_time.second);
  } else {
    sekunden = String(a_time.second);
  }

  return stunden + "." + minuten + "." + sekunden;
}

class RTC {
public:
  RTC(uint16_t a_i2cAdress) {
    Wire.begin();
    m_i2cAdress = a_i2cAdress;
  }

  void set(Time a_time) {
    Wire.beginTransmission(DS3231_I2C_ADDRESS);
    Wire.write(0);
    Wire.write(decToHex(a_time.second));
    Wire.write(decToHex(a_time.minute));
    Wire.write(decToHex(a_time.hour));
    Wire.write(decToHex(a_time.weekday));
    Wire.endTransmission();
  }

  Time read() const {
    Wire.beginTransmission(DS3231_I2C_ADDRESS);
    Wire.write(0); // gibt O Uhr vor
    Wire.endTransmission();

    //7 Bytes werden vom RTC abgefragt
    Time time;
    Wire.requestFrom(DS3231_I2C_ADDRESS, 4);
    time.second = hexToDec(Wire.read() & 0x7f);
    time.minute = hexToDec(Wire.read());
    time.hour = hexToDec(Wire.read() & 0x3f);
    time.weekday = (Weekday) hexToDec(Wire.read());
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
  uint16_t m_i2cAdress = 0;
};