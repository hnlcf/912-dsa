#ifndef INC_912_DSA_DS_FIB_H_
#define INC_912_DSA_DS_FIB_H_

#include <ds/autoheader.h>

namespace dsa {
class Fib {
 private:
  size_type f;
  size_type g;

 public:
  /// @brief Construct the First fibonacci number that is not less than `n`
  explicit Fib(size_type n) {
    f = 1;
    g = 0;
    while (g < n) {
      Next();
    }
  }

  /// @brief Return the current fibonacci number
  size_type Get() const { return g; }

  /// @brief Move to the Next fibonacci number
  size_type Next() {
    g += f;
    f = g - f;
    return g;
  }

  /// @brief Move to the previous fibonacci number
  size_type Prev() {
    f = g - f;
    g -= f;
    return g;
  }
};
}  // namespace dsa

#endif
