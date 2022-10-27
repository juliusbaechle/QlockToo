#ifndef CLOCK__H
#define CLOCK__H

#include <NTPClient.h>
#include <WiFiUdp.h>
#include "Time.h"

class Clock {
public:
  Clock();

  void update();
  Time currentTime();

private:
  Time getNTPTime();
  void setRTCTime(Time a_time);

private:
  WiFiUDP m_ntpUDP;
  NTPClient m_timeClient{ m_ntpUDP, "europe.pool.ntp.org" };
  uint64_t m_nextUpdateMs = 0;
};

#endif
