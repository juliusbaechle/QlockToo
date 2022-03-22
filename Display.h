#pragma once

#include "PixelSet.h"
#include <Adafruit_NeoPixel.h>

#define LED_PIN 18 //Pin des LED-Bands
#define NUMPIXELS 114 //Anzahl der LEDs
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LED_PIN, NEO_RGBW + NEO_KHZ800); //Inizialisierung der NeoPixels Bibliothek

const set<uint8_t> heart = { 104, 94, 92, 80, 84, 74, 68, 56, 64, 54, 44, 43, 33, 31, 23, 38, 28, 26, 14, 13, 18, 19 };
const set<uint8_t> kati = { 0, 1, 2, 3 };
const set<uint8_t> andi = { 37, 38, 39, 40 };
const set<uint8_t> wilma = { 26, 27, 28, 37, 38 };

const set<uint8_t> vor = { 41, 42, 43 };
const set<uint8_t> nach = { 33, 34, 35, 36 };
const set<uint8_t> fuenf = { 25, 24, 23, 22 };
const set<uint8_t> zehn = { 32, 31, 30, 29 };
const set<uint8_t> viertl = { 15, 16, 17, 18, 19, 20 };
const set<uint8_t> halb = { 54, 53,52, 51 };
const set<uint8_t> dreiviertl = { 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };

const set<uint8_t> oise = { 55, 56, 57, 58 };
const set<uint8_t> zwoie = { 76, 75, 74, 73, 72 };
const set<uint8_t> dreie = { 77, 78, 79, 80, 81 };
const set<uint8_t> viere = { 105, 106, 107, 108, 109 };
const set<uint8_t> fuenfe = { 49, 48, 47, 46, 45 };
const set<uint8_t> sechse = { 57, 58, 59, 60, 61, 62 };
const set<uint8_t> siebne = { 99, 100, 101, 102, 103, 104 };
const set<uint8_t> achte = { 71, 70, 69, 68, 67 };
const set<uint8_t> neune = { 95, 94, 93, 92, 91 };
const set<uint8_t> zehne = { 98, 97, 96, 95, 94 };
const set<uint8_t> elfe = { 62, 63, 64, 65 };
const set<uint8_t> zwoelfe = { 82, 83, 84, 85, 86, 87 };

const set<uint8_t> es = { 10, 9 };
const set<uint8_t> isch = { 7, 6, 5, 4 };

set<uint8_t> getCorners(uint8_t a_minute) {
  set<uint8_t> leds;
  if (a_minute == 1)
    leds += 112;
  if (a_minute == 2)
    leds += 111;
  if (a_minute == 3)
    leds += 110;
  if (a_minute == 4)
    leds += 113;
  return leds;
}

set<uint8_t> getMinutes(uint8_t a_minute) {  
  if (a_minute >= 5 && a_minute < 10)
    return fuenf + nach;
  if (a_minute >= 10 && a_minute < 15)
    return zehn + nach;
  if (a_minute >= 15 && a_minute < 20)
    return viertl;
  if (a_minute >= 20 && a_minute < 25)
    return zehn + vor + halb;
  if (a_minute >= 25 && a_minute < 30)
    return fuenf + vor + halb;
  if (a_minute >= 30 && a_minute < 35)
    return halb;
  if (a_minute >= 35 && a_minute < 40)
    return fuenf + nach + halb;
  if (a_minute >= 40 && a_minute < 45)
    return zehn + nach + halb;
  if (a_minute >= 45 && a_minute < 50)
    return dreiviertl;
  if (a_minute >= 50 && a_minute < 55)
    return zehn + vor;
  if (a_minute >= 55 && a_minute < 60)
    return fuenf + vor;  
  return {};
}

set<uint8_t> getHours(uint8_t a_hour) {
  if (a_hour == 0) return zwoelfe;
  if (a_hour == 1) return oise;
  if (a_hour == 2) return zwoie;
  if (a_hour == 3) return dreie;
  if (a_hour == 4) return viere;
  if (a_hour == 5) return fuenfe;
  if (a_hour == 6) return sechse;
  if (a_hour == 7) return siebne;
  if (a_hour == 8) return achte;
  if (a_hour == 9) return neune;
  if (a_hour == 10) return zehne;
  if (a_hour == 11) return elfe;
  if (a_hour == 12) return zwoelfe;
}

inline uint8_t hoursToDisplay(uint8_t a_hour, uint8_t a_minute) {
  uint8_t hour = a_hour;
  if (a_minute > 15)
    hour++;
  if (hour > 12)
    hour -= 12;
  return hour;
}

void display(const set<uint8_t>& a_leds, uint32_t a_color) {
  for (int i = 0; i < NUMPIXELS; i++)
    a_leds.contains(i)
      ? pixels.setPixelColor(i, a_color)
      : pixels.setPixelColor(i, a_color);
  pixels.show();
}

void displayTime(Time a_time, uint32_t a_color) {
  set<uint8_t> leds;
  leds += getCorners(a_time.minute % 5);
  leds += es + isch;
  leds += getMinutes(a_time.minute);
  leds += getHours(hoursToDisplay(a_time.hour, a_time.minute));
  display(leds, a_color);
}