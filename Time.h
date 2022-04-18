#ifndef TIME__H
#define TIME__H

#include <stdint.h>
#include <WString.h>

struct Time {
  uint8_t hour = 0;
  uint8_t minute = 0;
  uint8_t second = 0;

  static String toMinString(Time a_time) {
    String strHour = a_time.hour > 9 ? String(a_time.hour) : "0" + String(a_time.hour);
    String strMinute = a_time.minute > 9 ? String(a_time.minute) : "0" + String(a_time.minute);
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

  bool operator <  (const Time& a_time) { return compare(a_time) == -1; }
  bool operator <= (const Time& a_time) { return compare(a_time) !=  1; }
  bool operator == (const Time& a_time) { return compare(a_time) ==  0; }
  bool operator != (const Time& a_time) { return compare(a_time) !=  0; }
  bool operator >= (const Time& a_time) { return compare(a_time) != -1; }
  bool operator >  (const Time& a_time) { return compare(a_time) ==  1; }

private:
  int compare(const Time& a_time) const {
    if (hour > a_time.hour) return 1;
    if (hour < a_time.hour) return -1;
    if (minute > a_time.minute) return 1;
    if (minute < a_time.minute) return -1;
    if (second > a_time.second) return 1;
    if (second < a_time.second) return -1;
    return 0;
  }
};

#endif
