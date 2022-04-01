#ifndef CONFIGURATION__H
#define CONFIGURATION__H

#include "Time.h"
#include "Color.h"

class Configuration {
public:
  static Configuration load();

  String httpUsername() const { return m_httpUsername; }
  void setHttpUsername(String a_username) { m_httpUsername = a_username; save(); }

  String httpPassword() const { return m_httpPassword; }
  void setHttpPassword(String a_password) { m_httpPassword = a_password; save(); }

  Color color() const { return m_color; }
  void setColor(Color a_color) { m_color = a_color; save(); }

  Time startupTime() const { return m_startupTime; }
  void setStartupTime(Time a_time) { m_startupTime = a_time; save(); }

  Time shutdownTime() const { return m_shutdownTime; }
  void setShutdownTime(Time a_time) { m_shutdownTime = a_time; save(); }

  bool adaptiveLuminosity() const { return m_adaptiveLuminosity; }
  void setAdaptiveLuminosity(bool a_autoBrightness) { m_adaptiveLuminosity = a_autoBrightness; save(); }

  int8_t utcOffset() const { return m_utcOffset; }
  void setUtcOffset(int8_t a_offset) { m_utcOffset = a_offset; save(); }

  String wifiSsid() const { return m_wifiSsid; }
  void setWifiSsid(String a_ssid) { m_wifiSsid = a_ssid; save(); }

  String wifiPassword() const { return m_wifiPassword; }
  void setWifiPassword(String a_password) { m_wifiPassword = a_password; save(); }

private:
  void save();

private:
  String m_wifiPassword;
  String m_wifiSsid;
  int8_t m_utcOffset;
  String m_httpUsername;
  String m_httpPassword;
  Time m_startupTime;
  Time m_shutdownTime;
  Color m_color;
  bool m_adaptiveLuminosity;
};

#endif
