#ifndef GERMAN_DISPLAY__H
#define GERMAN_DISPLAY__H

#include "Display.h"

class GermanDisplay : public Display {
public:
  GermanDisplay(const std::map<String, set<uint8_t>>& a_specials, bool a_useDreiviertel = false);

  void displayTime(Time a_time, Color a_foreground, Color a_background) override;

private:
  set<uint8_t> getMinutes(uint8_t a_minute);
  set<uint8_t> getHours(uint8_t a_hour, uint8_t a_minute);

private:
  bool m_useDreiviertel;
};

#endif
