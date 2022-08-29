#ifndef INC_912_DSA_DS_STACK_INTERFACE_H_
#define INC_912_DSA_DS_STACK_INTERFACE_H_

namespace dsa {
template <class T>
class StackInterface {
 public:
  virtual void push(T const& e) = 0;
  virtual T    pop()            = 0;
  virtual T&   top()            = 0;
  virtual bool isEmpty() const  = 0;
};
}  // namespace dsa

#endif
