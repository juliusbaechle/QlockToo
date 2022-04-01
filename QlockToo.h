#ifndef QLOCKTOO__H
#define QLOCKTOO__H

#include "Display.h"
#include "QlockClock.h"
#include "Configuration.h"

class QlockToo {
public:
  QlockToo(Display& a_display) : m_display(a_display) {};
  void initialize();

  void update();

  String httpUsername() const { return m_config.httpUsername(); }
  void setHttpUsername(String a_username) { m_config.setHttpUsername(a_username); }

  String httpPassword() const { return m_config.httpPassword(); }
  void setHttpPassword(String a_password) { m_config.setHttpPassword(a_password); }

  String wifiSsid() const { return m_config.wifiSsid(); }
  void setWifiSsid(String a_ssid) { m_config.setWifiSsid(a_ssid); }

  String wifiPassword() const { return m_config.wifiPassword(); }
  void setWifiPassword(String a_password) { m_config.setWifiPassword(a_password); }

  Color color() const { return m_config.color(); }
  void setColor(Color a_color);

  bool adaptiveLuminosity() const { return m_config.adaptiveLuminosity(); }
  void setAdaptiveLuminosity(bool a_autoBrightness);

  int8_t utcOffset() const { return m_config.utcOffset(); }
  void setUtcOffset(int8_t a_offset);

  bool isActive() const { return m_active; }
  void setActive(bool a_active);

  std::vector<String> possibleSpecials() const { return m_display.possibleSpecials(); }
  String getSpecial() const { return m_special; }
  void setSpecial(const String& a_special);
  
  Time startupTime() const { return m_config.startupTime(); }
  void setStartupTime(Time a_time);

  Time shutdownTime() const { return m_config.shutdownTime(); }
  void setShutdownTime(Time a_time);

private:
  void updateNightMode(Time a_time);
  void onNightTimeChanged();
  void updateDisplay();
  uint8_t getAutoBrightness();
  uint8_t getRelBrightnessPerc();

private:
  Display& m_display;
  Configuration m_config;
  QlockClock m_clock;
  uint64_t m_nextDisplayUpdateMs = 0;
  String m_special = "";
  bool m_active = true;
};

#endif
