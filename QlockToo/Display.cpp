#include "Display.h"
#define NUMPIXELS 114
#define LED_PIN 18

Display::Display(const std::map<String, set<uint8_t>>& a_specials) 
  : m_pixels(NUMPIXELS, LED_PIN, NEO_GRBW + NEO_KHZ800) 
  , m_specials(a_specials)
{
  m_pixels.begin();
}

set<uint8_t> Display::getCorners(uint8_t a_minute) {
  set<uint8_t> leds;
  if (a_minute >= 1)
    leds += 112;
  if (a_minute >= 2)
    leds += 111;
  if (a_minute >= 3)
    leds += 110;
  if (a_minute >= 4)
    leds += 113;
  return leds;
}

uint32_t Display::toInt(Color a_color) {
  uint8_t w = min({ a_color.r, a_color.g, a_color.b });
  return Adafruit_NeoPixel::Color(a_color.r - w, a_color.g - w, a_color.b - w, w);
}

void Display::display(const set<uint8_t>& a_leds, Color a_foreground, Color a_background) {
  uint32_t foreground = toInt(a_foreground);
  uint32_t background = toInt(a_background);

  for (int i = 0; i < NUMPIXELS; i++)
    a_leds.contains(i)
    ? m_pixels.setPixelColor(i, foreground)
    : m_pixels.setPixelColor(i, background);
  m_pixels.show();
}

void Display::displaySpecial(String a_special, Color a_foreground, Color a_background) {
  set<uint8_t> leds = m_specials.at(a_special);
  display(leds, a_foreground, a_background);
}

std::vector<String> Display::possibleSpecials() const {
  std::vector<String> possibleSpecials;
  for (auto it = m_specials.begin(); it != m_specials.end(); it++)
    possibleSpecials.push_back(it->first);
  return possibleSpecials;
}