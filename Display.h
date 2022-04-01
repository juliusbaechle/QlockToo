#ifndef DISPLAY__H
#define DISPLAY__H

#include "PixelSet.h"
#include <Adafruit_NeoPixel.h>

#define LED_PIN 18
#define NUMPIXELS 114
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LED_PIN, NEO_GRBW + NEO_KHZ800);

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

void display(const set<uint8_t>& a_leds, uint32_t a_color) {
  for (int i = 0; i < NUMPIXELS; i++)
    a_leds.contains(i)
    ? pixels.setPixelColor(i, a_color)
    : pixels.setPixelColor(i, 0);
  pixels.show();
}

// const set<uint8_t> heart = { 104, 94, 92, 80, 84, 74, 68, 56, 64, 54, 44, 43, 33, 31, 23, 38, 28, 26, 14, 13, 18, 19 };
// const set<uint8_t> kati = { 0, 1, 2, 3 };
// const set<uint8_t> andi = { 37, 38, 39, 40 };
// const set<uint8_t> wilma = { 26, 27, 28, 37, 38 };
// const set<uint8_t> nini = { 36, 37, 38, 39, 59, 60, 61, 73, 72 };

#endif
