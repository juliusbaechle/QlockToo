#pragma once

#include "MySet.h"
#include "Arduino.h"
#include <map>

const std::map<String, set<uint8_t>> specials = {
  { "Herz", { 104, 94, 92, 80, 84, 74, 68, 56, 64, 54, 44, 43, 33, 31, 23, 38, 28, 26, 14, 13, 18, 19 } },
  { "Julius", { 26, 27, 28, 37, 38, 39 } },
};
