#ifndef INC_912_DSA_DS_STACK_H_
#define INC_912_DSA_DS_STACK_H_

#include <autoheader.h>
#include <stack_interface.h>
#include <vector.h>

namespace dsa {
template <typename T>
class Stack : public IStack<T> {
 private:
  Vector<T>* m_vector;

 public:
  Stack() { m_vector = new Vector<T>; };

  ~Stack() {
    delete m_vector;
    m_vector = nullptr;
  };

  void push(T const& e) override { m_vector->push_back(e); }

  T pop() override { return m_vector->pop_back(); }

  T& top() override { return (*m_vector)[m_vector->size() - 1]; }

  bool isEmpty() const override { return m_vector->size() == 0; }
};
}  // namespace dsa

#endif