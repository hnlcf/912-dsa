#ifndef INC_912_DSA_DS_ITERATOR_H_
#define INC_912_DSA_DS_ITERATOR_H_

#include <autoheader.h>

namespace dsa {
template <class T>
class Iterator {
 public:
  /* An iterator class must declare(public) the following types */
  using difference_type = std::ptrdiff_t;
  using value_type = T;
  using pointer = T*;
  using reference = T&;
  using iterator_category = std::forward_iterator_tag;

 public:
  /* An iterator class must implement(public) the following operator overloads
   */
  Iterator() : m_ptr(nullptr) {}

  explicit Iterator(pointer p) : m_ptr(p) {}

  Iterator(const Iterator& other) : m_ptr(other.base()) {}

  pointer operator->() const { return m_ptr; }

  reference operator*() { return *m_ptr; }

  Iterator& operator++() {
    ++m_ptr;
    return *this;
  }

  Iterator operator++(int) { return Iterator(m_ptr++); }

  Iterator& operator--() {
    --m_ptr;
    return *this;
  }

  Iterator operator--(int) { return Iterator(m_ptr--); }

  reference operator[](difference_type n) const { return m_ptr[n]; }

  Iterator& operator+=(difference_type n) {
    m_ptr += n;
    return *this;
  }

  Iterator operator+(difference_type n) { return Iterator(m_ptr + n); }

  Iterator& operator-=(difference_type n) {
    m_ptr -= n;
    return *this;
  }

  Iterator operator-(difference_type n) { return Iterator(m_ptr - n); }

  const pointer& base() const { return m_ptr; }

  Iterator& operator=(const Iterator& iter) {
    if (this == &iter) {
      return *this;
    }
    m_ptr = iter.m_ptr;
    return *this;
  }

  bool operator!=(const Iterator& iter) { return m_ptr != iter.m_ptr; }

  bool operator==(const Iterator& iter) { return m_ptr == iter.m_ptr; }

  bool operator<(const Iterator& iter) const { return m_ptr < iter.m_ptr; }

  bool operator>(const Iterator& iter) const { return m_ptr > iter.m_ptr; }

  bool operator<=(const Iterator& iter) const {
    return *this < iter || *this == iter;
  }

  bool operator>=(const Iterator& iter) const {
    return *this > iter || *this == iter;
  }

 private:
  pointer m_ptr;
};
}  // namespace dsa

#endif