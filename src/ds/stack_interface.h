#ifndef INC_912_DSA_DS_STACK_INTERFACE_H_
#define INC_912_DSA_DS_STACK_INTERFACE_H_

#include "autoheader.h"

namespace dsa {
template <typename T>
class IStack {
 public:
  virtual void Push(T const& e) = 0;
  virtual T Pop() = 0;
  virtual T& Top() = 0;
  virtual bool IsEmpty() const = 0;
};
}  // namespace dsa

#endif
