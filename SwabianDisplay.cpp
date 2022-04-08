#include "SwabianDisplay.h"

const set<uint8_t> es = { 10, 9 };
const set<uint8_t> isch = { 7, 6, 5, 4 };

const set<uint8_t> fuenf = { 25, 24, 23, 22 };
const set<uint8_t> zehn = { 32, 31, 30, 29 };
const set<uint8_t> vor = { 41, 42, 43 };
const set<uint8_t> nach = { 33, 34, 35, 36 };
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

set<uint8_t> SwabianDisplay::getMinutes(uint8_t a_minute) {
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

set<uint8_t> SwabianDisplay::getHours(uint8_t a_hour, uint8_t a_minute) {
  uint8_t hour = (a_hour + (a_minute >= 15)) % 12;
  if (hour == 0) return zwoelfe;
  if (hour == 1) return oise;
  if (hour == 2) return zwoie;
  if (hour == 3) return dreie;
  if (hour == 4) return viere;
  if (hour == 5) return fuenfe;
  if (hour == 6) return sechse;
  if (hour == 7) return siebne;
  if (hour == 8) return achte;
  if (hour == 9) return neune;
  if (hour == 10) return zehne;
  if (hour == 11) return elfe;
  return {};
}

void SwabianDisplay::displayTime(Time a_time, Color a_foreground, Color a_background) {
  set<uint8_t> leds;
  leds += getCorners(a_time.minute % 5);
  leds += es + isch;
  leds += getMinutes(a_time.minute);
  leds += getHours(a_time.hour, a_time.minute);
  display(leds, a_foreground, a_background);
}
