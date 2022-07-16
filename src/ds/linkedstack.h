#ifndef INC_912_DSA_DS_LINKEDSTACK_H_
#define INC_912_DSA_DS_LINKEDSTACK_H_

#include "autoheader.h"
#include "list.h"
#include "stack_interface.h"

namespace dsa {
template <typename T>
class LinkedStack : public IStack<T> {
 private:
  List<T> list;

 public:
  LinkedStack() = default;
  ~LinkedStack() = default;

  void push(T const& e) override { list.insertAsLast(e); }

  T pop() override { return list.remove(list.last()); }

  T& top() override { return list[list.size() - 1]; }

  bool isEmpty() const override { return list.size() == 0; }
};
}  // namespace dsa

#endif
