#ifndef DISPLAY__H
#define DISPLAY__H

#include "Time.h"
#include "Color.h"
#include "MySet.h"
#include <map>
#include <Adafruit_NeoPixel.h>

class Display {
public:
  Display(const std::map<String, set<uint8_t>>& a_specials);
  virtual ~Display() = default;

  virtual void displayTime(Time a_time, Color a_color) = 0;
  void displaySpecial(String a_special, Color a_color);
  std::vector<String> possibleSpecials() const;

protected:
  void display(const set<uint8_t>& a_leds, Color a_color);
  set<uint8_t> getCorners(uint8_t a_minute);
  uint32_t toInt(Color a_color);

private:
  std::map<String, set<uint8_t>> m_specials;
  Adafruit_NeoPixel m_pixels;
};

#endif
