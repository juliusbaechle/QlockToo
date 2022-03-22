#pragma once

#include <Wire.h>

enum Weekday {
  Sunday,
  Monday,
  Tuesday,
  Wednesday,
  Thursday,
  Friday,
  Saturday
};

String toString(Weekday a_weekday) {
  if (a_weekday == Weekday::Monday)
    return "Monday";
  if (a_weekday == Weekday::Tuesday)
    return "Tuesday";
  if (a_weekday == Weekday::Wednesday)
    return "Wednesday";
  if (a_weekday == Weekday::Thursday)
    return "Thursday";
  if (a_weekday == Weekday::Friday)
    return "Friday";
  if (a_weekday == Weekday::Saturday)
    return "Saturday";
  return "Sunday";
}

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
    Wire.beginTransmission(m_i2cAdress);
    Wire.write(0);
    Wire.write(decToHex(a_time.second));
    Wire.write(decToHex(a_time.minute));
    Wire.write(decToHex(a_time.hour));
    Wire.write(decToHex(a_time.weekday));
    Wire.endTransmission();
  }

  Time read() const {
    Wire.beginTransmission(m_i2cAdress);
    Wire.write(0); // gibt O Uhr vor
    Wire.endTransmission();

    //7 Bytes werden vom RTC abgefragt
    Time time;
    Wire.requestFrom(m_i2cAdress, 4);
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
  int m_i2cAdress = 0;
};