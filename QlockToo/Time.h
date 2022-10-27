#ifndef TIME__H
#define TIME__H

#include <stdint.h>
#include <WString.h>

struct Time {
  uint8_t hour = 0;
  uint8_t minute = 0;
  uint8_t second = 0;

  static String toMinString(Time a_time);
  static Time parseMinString(const String& a_str);

  void addHours(int32_t a_hours);

  bool operator <  (const Time& a_time) { return compare(a_time) == -1; }
  bool operator <= (const Time& a_time) { return compare(a_time) !=  1; }
  bool operator == (const Time& a_time) { return compare(a_time) ==  0; }
  bool operator != (const Time& a_time) { return compare(a_time) !=  0; }
  bool operator >= (const Time& a_time) { return compare(a_time) != -1; }
  bool operator >  (const Time& a_time) { return compare(a_time) ==  1; }

private:
  int compare(const Time& a_time) const;
};

#endif
