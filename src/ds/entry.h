#ifndef INC_912_DSA_DS_ENTRY_H_
#define INC_912_DSA_DS_ENTRY_H_

#include <ds/autoheader.h>

namespace dsa {
template <class KeyType, class ValueType>
struct Entry {
  KeyType   m_key;
  ValueType m_value;

  Entry() : Entry(KeyType(), ValueType()) {}

  Entry(KeyType k, ValueType v) : m_key(k), m_value(v) {}

  Entry(Entry<KeyType, ValueType> const& other)
      : Entry(other.m_key, other.m_value) {}

  bool operator<(Entry<KeyType, ValueType> const& other) {
    return m_key < other.m_key;
  }

  bool operator>(Entry<KeyType, ValueType> const& other) {
    return m_key > other.m_key;
  }

  bool operator==(Entry<KeyType, ValueType> const& other) {
    return m_key == other.m_key;
  }

  bool operator!=(Entry<KeyType, ValueType> const& other) {
    return m_key != other.m_key;
  }
};
}  // namespace dsa

#endif
