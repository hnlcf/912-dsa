#ifndef INC_912_DSA_DS_QUEUE_H_
#define INC_912_DSA_DS_QUEUE_H_

#include "autoheader.h"
#include "list.h"

namespace dsa {
template <typename T>
class Queue {
 private:
  List<T> m_elem;

 public:
  void enqueue(const T& e) { m_elem.insertAsLast(e); }

  T dequeue() {
    auto tmp = m_elem.first();
    return m_elem.remove(tmp);
  }

  T first() {
    if (size() > 0) {
      return m_elem[0];
    }
    return *(new T);  // return a random value
  }

  T last() {
    if (size() > 0) {
      return m_elem[size() - 1];
    }
    return *(new T);
  }

  size_type size() const { return m_elem.size(); }

  bool isEmpty() const { return m_elem.size() == 0; }
};
}  // namespace dsa

#endif
