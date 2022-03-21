#pragma once

#define DS3231_I2C_ADDRESS 0x68 //Adresse zur Kommunikation mit RTC

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

byte decToHex(byte val) {
  return ((val / 10 * 16) + (val % 10));
}

byte hexToDec(byte val) {
  return ((val / 16 * 10) + (val % 16));
}

void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek) {
  // sets time and date data to DS3231
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set next input to start at the seconds register
  Wire.write(decToHex(second)); // set seconds
  Wire.write(decToHex(minute)); // set minutes
  Wire.write(decToHex(hour)); // set hours
  Wire.write(decToHex(dayOfWeek)); // set day of week (1=Sunday, 7=Saturday)
  Wire.endTransmission();
}

void readDS3231time(byte* second, byte* minute, byte* hour, byte* dayOfWeek) {
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // gibt O Uhr vor
  Wire.endTransmission();

  //7 Bytes werden vom RTC abgefragt
  Wire.requestFrom(DS3231_I2C_ADDRESS, 4);
  *second = hexToDec(Wire.read() & 0x7f);
  *minute = hexToDec(Wire.read());
  *hour = hexToDec(Wire.read() & 0x3f);
  *dayOfWeek = hexToDec(Wire.read());
}