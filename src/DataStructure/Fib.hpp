
#pragma once

#include "Vector.hpp"
#include <cstdint>

using size_type = int64_t;

namespace dsa {
    class Fib {
    private:
        size_type f;
        size_type g;

    public:
        /// Construct the first fibonacci number that is not less than `n`
        Fib(size_type n) {
            f = 1;
            g = 0;
            while (g < n) {
                next();
            }
        }

        /// Return the current fibonacci number
        size_type get() {
            return g;
        }

        /// Move to the next fibonacci number
        size_type next() {
            g += f;
            f = g - f;
            return g;
        }

        /// Move to the previous fibonacci number
        size_type prev() {
            f = g - f;
            g -= f;
            return g;
        }
    };
}
