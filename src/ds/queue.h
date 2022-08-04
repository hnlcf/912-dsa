#ifndef INC_912_DSA_DS_QUEUE_H_
#define INC_912_DSA_DS_QUEUE_H_

#include <ds/autoheader.h>
#include <ds/list.h>

namespace dsa {
template <typename T>
class Queue {
 private:
  List<T> m_elem;

 public:
  void Enqueue(const T& e) { m_elem.InsertAsLast(e); }

  T Dequeue() {
    auto tmp = m_elem.First();
    return m_elem.Remove(tmp);
  }

  T First() {
    assert(Size() > 0);
    return m_elem[0];
  }

  T Last() {
    assert(Size() > 0);
    return m_elem[Size() - 1];
  }

  size_type Size() const { return m_elem.Size(); }

  bool IsEmpty() const { return m_elem.Size() == 0; }
};
}  // namespace dsa

#endif
