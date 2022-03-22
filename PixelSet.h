#pragma once

#include <set>

template<typename T>
class set {
public:
  set() = default;

  set(const std::initializer_list<T>& a_initializer)
    : m_set(a_initializer) {}

  set<T> operator+= (const set<T>& a_set) {
    m_set.insert(a_set.m_set.begin(), a_set.m_set.end());
  }

  set<T> operator+= (const T& a_item) {
    m_set.insert(a_item);
  }

  set<T> operator+ (const set<T>& a_set) const {
    set<T> l;
    l.m_set.insert(m_set.begin(), m_set.end());
    l.m_set.insert(a_set.m_set.begin(), a_set.m_set.end());
    return l;
  }

  set<T> operator+ (const T& a_item) const {
    set<T> l;
    l.m_set = m_set;
    l.m_set.push_back(a_item);
    return l;
  }

  bool contains(const T& a_item) const {
    return std::find(m_set.begin(), m_set.end(), a_item) != m_set.end();
  }

private:
  std::set<uint8_t> m_set;
};