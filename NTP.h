#pragma once

#include <NTPClient.h>
#include <WiFiUdp.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);

Time readTimeNTP() {
  Time time;
  time.hour = (uint8_t)timeClient.getHours();
  time.minute = (uint8_t)timeClient.getMinutes();
  time.second = (uint8_t)timeClient.getSeconds();
  return time;
}