#pragma once

#include "MySet.h"
#include "Arduino.h"
#include <map>

const std::map<String, set<uint8_t>> specials = {
  { "Herz", { 104, 94, 92, 80, 84, 74, 68, 56, 64, 54, 44, 43, 33, 31, 23, 38, 28, 26, 14, 13, 18, 19 } },
  { "Kati", { 0, 1, 2, 3 } },
  { "Andi", { 37, 38, 39, 40 } },
  { "Wilma", { 26, 27, 28, 37, 38 } },
  { "Nini", { 36, 37, 38, 39, 59, 60, 61, 73, 72 } }
};
