
#pragma once

#include "Vector.hpp"

using Rank = int;

namespace dsa {
    class Fib {
    private:
        Rank f;
        Rank g;

    public:
        /// Construct the first fibonacci number that is not less than `n`
        Fib(Rank n) {
            f = 1;
            g = 0;
            while (g < n) {
                next();
            }
        }

        /// Return the current fibonacci number
        Rank get() {
            return g;
        }

        /// Move to the next fibonacci number
        Rank next() {
            g += f;
            f = g - f;
            return g;
        }

        /// Move to the previous fibonacci number
        Rank prev() {
            f = g - f;
            g -= f;
            return g;
        }
    };
}