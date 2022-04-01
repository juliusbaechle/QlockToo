#ifndef TIME__H
#define TIME__H

#include <stdint.h>
#include <WString.h>

struct Time {
  uint8_t hour = 0;
  uint8_t minute = 0;
  uint8_t second = 0;

  bool operator< (const Time& a_time) const {
    if (hour < a_time.hour)
      return true;
    if (minute < a_time.minute)
      return true;
    if (second < a_time.second)
      return true;
    return false;
  }

  bool operator== (const Time& a_time) const {
    if (hour != a_time.hour)
      return false;
    if (minute != a_time.minute)
      return false;
    if (second != a_time.second)
      return false;
    return true;
  }

  String toMinString() const {
    String strHour = hour > 9 ? String(hour) : "0" + String(hour);
    String strMinute = minute > 9 ? String(minute) : "0" + String(minute);
    return strHour + ":" + strMinute;
  }

  static Time parseMinString(const String& a_str) {
    Time time;
    time.hour = a_str.substring(0, 2).toInt();
    time.minute = a_str.substring(3, 5).toInt();
    time.second = 0;
    return time;
  }

  void addHours(int32_t a_hours) {
    a_hours %= 24;
    if (a_hours < 0)
      a_hours += 24;
    hour += a_hours;
    hour %= 24;
  }
};

#endif