#ifndef INC_912_DSA_DS_LINKEDSTACK_H_
#define INC_912_DSA_DS_LINKEDSTACK_H_

#include <ds/list.h>
#include <ds/stack_interface.h>

namespace dsa {
template <typename T>
class LinkedStack : public IStack<T> {
 private:
  List<T> list;

 public:
  LinkedStack() = default;
  ~LinkedStack() = default;

  void Push(T const& e) override { list.InsertAsLast(e); }

  T Pop() override { return list.Remove(list.Last()); }

  T& Top() override { return list[list.Size() - 1]; }

  bool IsEmpty() const override { return list.Size() == 0; }
};
}  // namespace dsa

#endif
