#ifndef COLOR__H
#define COLOR__H

#include <stdint.h>
#include <WString.h>

struct Color {
  uint8_t r = 255;
  uint8_t g = 255;
  uint8_t b = 255;

  Color() = default;  
  Color(uint8_t r, uint8_t g, uint8_t b);
  Color& dimm(uint8_t a_perc);

  static Color parse(const String& a_str);
  static String toString(const Color& a_color);
};

#endif
