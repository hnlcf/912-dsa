#ifndef INC_912_DSA_DS_STACK_H_
#define INC_912_DSA_DS_STACK_H_

#include <ds/stack_interface.h>
#include <ds/vector.h>

namespace dsa {
template <typename T>
class Stack : public StackInterface<T> {
 private:
  Vector<T>* m_vector;

 public:
  Stack() { m_vector = new Vector<T>(); };

  ~Stack() {
    delete m_vector;
    m_vector = nullptr;
  };

  void Push(T const& e) override { m_vector->PushBack(e); }

  T Pop() override { return m_vector->PopBack(); }

  T& Top() override { return (*m_vector)[m_vector->Size() - 1]; }

  bool IsEmpty() const override { return m_vector->Size() == 0; }
};
}  // namespace dsa

#endif
