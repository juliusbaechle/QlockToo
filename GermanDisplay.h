#ifndef GERMANDISPLAY__H
#define GERMANDISPLAY__H

#include "Display.h"

const set<uint8_t> es = { 10, 9 };
const set<uint8_t> ist = { 7, 6, 5 };

const set<uint8_t> fuenf_min = { 3, 2, 1, 0 };
const set<uint8_t> zehn_min = { 11, 12, 13, 14 };
const set<uint8_t> vor = { 33, 34, 35 };
const set<uint8_t> nach = { 40, 41, 42, 43 };
const set<uint8_t> viertel = { 28, 27, 26, 25, 24, 23, 22 };
const set<uint8_t> halb = { 54, 53, 52, 51 };
const set<uint8_t> dreiviertel = { 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22 };

const set<uint8_t> ein = { 55, 56, 57 };
const set<uint8_t> eins = { 55, 56, 57, 58 };
const set<uint8_t> zwei = { 62, 63, 64, 65 };
const set<uint8_t> drei = { 76, 75, 74, 73 };
const set<uint8_t> vier = { 69, 68, 67, 66 };
const set<uint8_t> fuenf = { 47, 46, 45, 44 };
const set<uint8_t> sechs = { 77, 78, 79, 80, 81 };
const set<uint8_t> sieben = { 98, 97, 96, 95, 94, 93 };
const set<uint8_t> acht = { 84, 85, 86, 87 };
const set<uint8_t> neun = { 102, 103, 104, 105 };
const set<uint8_t> zehn = { 99, 100, 101, 102 };
const set<uint8_t> elf = { 49, 48, 47 };
const set<uint8_t> zwoelf = { 92, 91, 90, 89, 88 };

const set<uint8_t> uhr = { 107, 108, 109 };


set<uint8_t> getMinutes(uint8_t a_minute) {
  if (a_minute >= 5 && a_minute < 10)
    return fuenf_min + nach;
  if (a_minute >= 10 && a_minute < 15)
    return zehn_min + nach;
  if (a_minute >= 15 && a_minute < 20)
    return viertel;
  if (a_minute >= 20 && a_minute < 25)
    return zehn_min + vor + halb;
  if (a_minute >= 25 && a_minute < 30)
    return fuenf_min + vor + halb;
  if (a_minute >= 30 && a_minute < 35)
    return halb;
  if (a_minute >= 35 && a_minute < 40)
    return fuenf_min + nach + halb;
  if (a_minute >= 40 && a_minute < 45)
    return zehn_min + nach + halb;
  if (a_minute >= 45 && a_minute < 50)
    return dreiviertel;
  if (a_minute >= 50 && a_minute < 55)
    return zehn_min + vor;
  if (a_minute >= 55 && a_minute < 60)
    return fuenf_min + vor;
  return {};
}

set<uint8_t> getHours(uint8_t a_hour, uint8_t a_minute) {
  uint8_t hour = (a_hour + (a_minute > 15)) % 12;
  bool full = (0 <= a_minute && a_minute < 5);

  set<uint8_t> leds;
  if (hour == 0) leds += zwoelf;
  if (hour == 1 && full) leds += ein;
  if (hour == 1 && !full) leds += eins;
  if (hour == 2) leds += zwei;
  if (hour == 3) leds += drei;
  if (hour == 4) leds += vier;
  if (hour == 5) leds += fuenf;
  if (hour == 6) leds += sechs;
  if (hour == 7) leds += sieben;
  if (hour == 8) leds += acht;
  if (hour == 9) leds += neun;
  if (hour == 10) leds += zehn;
  if (hour == 11) leds += elf;
  if (full) leds += uhr;
  return leds;
}

void displayTime(Time a_time, uint32_t a_color) {
  set<uint8_t> leds;
  leds += getCorners(a_time.minute % 5);
  leds += es + ist;
  leds += getMinutes(a_time.minute);
  leds += getHours(a_time.hour, a_time.minute);
  display(leds, a_color);
}

#endif
