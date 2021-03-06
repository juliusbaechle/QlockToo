#ifndef SWABIAN_DISPLAY__H
#define SWABIAN_DISPLAY__H

#include "Display.h"

class SwabianDisplay : public Display {
public:
  SwabianDisplay(const std::map<String, set<uint8_t>> a_specials) : Display(a_specials) {};

  void displayTime(Time a_time, Color a_foreground, Color a_background) override;

private:
  set<uint8_t> getMinutes(uint8_t a_minute);
  set<uint8_t> getHours(uint8_t a_hour, uint8_t a_minute);
};

#endif
