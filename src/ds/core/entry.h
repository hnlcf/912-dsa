#ifndef INC_912_DSA_DS_ENTRY_H_
#define INC_912_DSA_DS_ENTRY_H_

#include <ds/utils/autoheader.h>

namespace dsa {
template <class Key, class Value>
struct Entry {
  Key   m_key;
  Value m_value;

  Entry() : Entry(Key(), Value()) {}

  Entry(Key k, Value v) : m_key(k), m_value(v) {}

  Entry(Entry<Key, Value> const& other) : Entry(other.m_key, other.m_value) {}

  bool operator<(Entry<Key, Value> const& other) { return m_key < other.m_key; }

  bool operator>(Entry<Key, Value> const& other) { return m_key > other.m_key; }

  bool operator==(Entry<Key, Value> const& other) {
    return m_key == other.m_key;
  }

  bool operator!=(Entry<Key, Value> const& other) {
    return m_key != other.m_key;
  }
};
}  // namespace dsa

#endif
