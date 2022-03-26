#pragma once

#include "Time.h"
#include "Color.h"

class Configuration {
public:
  String username() const { return m_username; }
  void setUsername(String a_username) { m_username = a_username; }

  String password() const { return m_password; }
  void setPassword(String a_password) { m_password = a_password; }

  Color color() const { return m_color; }
  void setColor(Color a_color) { m_color = a_color; }

  Time startupTime() const { return m_startupTime; }
  void setStartupTime(Time a_time) { m_startupTime = a_time; }

  Time shutdownTime() const { return m_shutdownTime; }
  void setShutdownTime(Time a_time) { m_shutdownTime = a_time; }

  bool autoBrightness() const { return m_autoBrightness; }
  void setAutoBrightness(bool a_autoBrightness) { m_autoBrightness = a_autoBrightness; }

  bool isActiveTime(Time a_time) const {
    if (m_startupTime < m_shutdownTime) {
      return m_startupTime < a_time && a_time < m_shutdownTime;
    } else {
      return m_startupTime < a_time || a_time < m_shutdownTime;
    }
  }

private:
  String m_username = "admin";
  String m_password = "admin";
  Time m_startupTime;
  Time m_shutdownTime;
  Color m_color;
  bool m_autoBrightness = false;
};

Configuration config;