#pragma once

#include <AutoHeader.hpp>

namespace dsa {
  template<typename T>
  class IStack {
public:
    virtual void push(T const &e) = 0;
    virtual T    pop() = 0;
    virtual T   &top() = 0;
    virtual bool isEmpty() const = 0;
  };
}
