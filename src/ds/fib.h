#ifndef INC_912_DSA_DS_FIB_H_
#define INC_912_DSA_DS_FIB_H_

#include <autoheader.h>
#include <vector.h>
#include <cstdint>

namespace dsa {
class Fib {
 private:
  size_type f;
  size_type g;

 public:
  /// @brief Construct the first fibonacci number that is not less than `n`
  explicit Fib(size_type n) {
    f = 1;
    g = 0;
    while (g < n) {
      next();
    }
  }

  /// @brief Return the current fibonacci number
  size_type get() const { return g; }

  /// @brief Move to the next fibonacci number
  size_type next() {
    g += f;
    f = g - f;
    return g;
  }

  /// @brief Move to the previous fibonacci number
  size_type prev() {
    f = g - f;
    g -= f;
    return g;
  }
};
}  // namespace dsa

#endif