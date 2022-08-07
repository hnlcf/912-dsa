#ifndef INC_912_DSA_DS_QUEUE_H_
#define INC_912_DSA_DS_QUEUE_H_

#include <ds/utils/autoheader.h>
#include <ds/core/list.h>

namespace dsa {
template <class T>
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
    assert(size() > 0);
    return m_elem[0];
  }

  T last() {
    assert(size() > 0);
    return m_elem[size() - 1];
  }

  size_type size() const { return m_elem.size(); }

  bool isEmpty() const { return m_elem.size() == 0; }
};
}  // namespace dsa

#endif
