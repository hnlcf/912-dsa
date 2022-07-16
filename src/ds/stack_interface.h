#ifndef INC_912_DSA_DS_STACK_INTERFACE_H_
#define INC_912_DSA_DS_STACK_INTERFACE_H_

#include <autoheader.h>

namespace dsa {
template <typename T>
class IStack {
 public:
  virtual void push(T const& e) = 0;
  virtual T pop() = 0;
  virtual T& top() = 0;
  virtual bool isEmpty() const = 0;
};
}  // namespace dsa

#endif