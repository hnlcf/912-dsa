#ifndef INC_912_DSA_DS_STACK_H_
#define INC_912_DSA_DS_STACK_H_

#include <ds/core/stack_interface.h>
#include <ds/core/vector.h>

namespace dsa {
template <class T>
class Stack : public StackInterface<T> {
 private:
  Vector<T>* m_vector;

 public:
  Stack() { m_vector = new Vector<T>(); };

  ~Stack() {
    delete m_vector;
    m_vector = nullptr;
  };

  void push(T const& e) override { m_vector->pushBack(e); }

  T pop() override { return m_vector->popBack(); }

  T& top() override { return (*m_vector)[m_vector->size() - 1]; }

  bool isEmpty() const override { return m_vector->size() == 0; }
};
}  // namespace dsa

#endif
