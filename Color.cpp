#include "Color.h"

Color::Color(uint8_t r, uint8_t g, uint8_t b) {
  this->r = r;
  this->g = g;
  this->b = b;
}

Color Color::parse(const String& a_str) {
  int number = (int)strtol(&a_str.c_str()[1], NULL, 16);

  Color c;
  c.r = number >> 16;
  c.g = number >> 8 & 0xFF;
  c.b = number & 0xFF;
  return c;
}

String toHex(uint8_t a_number) {
  if (a_number == 0) {
    return "00";
  } else if (a_number < 16) {
    return "0" + String(a_number, 16);
  } else {
    return String(a_number, 16);
  }
}

String Color::toString() {
  String str = "#";
  str += toHex(r);
  str += toHex(g);
  str += toHex(b);
  return str;
}

Color& Color::dimm(uint8_t a_perc) {
  if (a_perc > 100)
    a_perc = 100;

  r = ((uint16_t)r * a_perc) / 100;
  g = ((uint16_t)g * a_perc) / 100;
  b = ((uint16_t)b * a_perc) / 100;
  return *this;
}