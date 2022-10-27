#ifndef QLOCKTOO__H
#define QLOCKTOO__H

#include "Display.h"
#include "Clock.h"
#include "Configuration.h"

class QlockToo {
public:
  QlockToo(Display& a_display) : m_display(a_display) {};
  void initialize();

  void update();

  String name() const { return m_config.name(); }
  void setName(String a_username) { m_config.setName(a_username); }

  String password() const { return m_config.password(); }
  void setPassword(String a_password) { m_config.setPassword(a_password); }

  String wifiSsid() const { return m_config.wifiSsid(); }
  void setWifiSsid(String a_ssid) { m_config.setWifiSsid(a_ssid); }

  String wifiPassword() const { return m_config.wifiPassword(); }
  void setWifiPassword(String a_password) { m_config.setWifiPassword(a_password); }

  Color foregroundColor() const { return m_config.foregroundColor(); }
  void setForegroundColor(Color a_color);

  Color backgroundColor() const { return m_backgroundColor; }
  void setBackgroundColor(Color a_color);

  bool adaptiveLuminosity() const { return m_config.adaptiveLuminosity(); }
  void setAdaptiveLuminosity(bool a_autoBrightness);

  int8_t utcOffset() const { return m_config.utcOffset(); }
  void setUtcOffset(int8_t a_offset);

  std::vector<String> possibleSpecials() const { return m_display.possibleSpecials(); }
  String special() const { return m_special; }
  void setSpecial(const String& a_special);
  
  Time startupTime() const { return m_config.startupTime(); }
  void setStartupTime(Time a_time);

  Time shutdownTime() const { return m_config.shutdownTime(); }
  void setShutdownTime(Time a_time);

  bool isInNightMode() { return m_nightMode; }

private:
  void updateDisplay();
  uint8_t getBrightness();
  bool isNightTime(Time a_time);

private:
  bool m_nightMode = false;
  Display& m_display;
  Configuration m_config;
  Clock m_clock;
  uint64_t m_nextDisplayUpdateMs = 0;
  String m_special = "";
  Color m_backgroundColor = { 0, 0, 0 };
};

#endif
