#ifndef DISPLAY__H
#define DISPLAY__H

#include "Color.h"
#include "PixelSet.h"
#include <Adafruit_NeoPixel.h>
#include <map>

#define LED_PIN 18
#define NUMPIXELS 114
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LED_PIN, NEO_GRBW + NEO_KHZ800);

const std::map<String, set<uint8_t>> specials = {
  { "heart", { 104, 94, 92, 80, 84, 74, 68, 56, 64, 54, 44, 43, 33, 31, 23, 38, 28, 26, 14, 13, 18, 19 } },
  { "kati", { 0, 1, 2, 3 } },
  { "andi", { 37, 38, 39, 40 } },
  { "wilma", { 26, 27, 28, 37, 38 } },
  { "nini", { 36, 37, 38, 39, 59, 60, 61, 73, 72 } }
};

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

uint32_t toInt(const Color& a_color) {
  uint8_t w = min({ a_color.r, a_color.g, a_color.b });
  return Adafruit_NeoPixel::Color(a_color.r - w, a_color.g - w, a_color.b - w, w);
}

void display(const set<uint8_t>& a_leds, const Color& a_color) {
  uint32_t color = toInt(a_color);
  for (int i = 0; i < NUMPIXELS; i++)
    a_leds.contains(i)
    ? pixels.setPixelColor(i, color)
    : pixels.setPixelColor(i, 0);
  pixels.show();
}

void displaySpecial(const String& a_special, const Color& a_color) {
  set<uint8_t> leds = specials.at(a_special);
  display(leds, a_color);
}

#endif
