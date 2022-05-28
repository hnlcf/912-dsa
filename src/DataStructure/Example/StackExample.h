#pragma once

#include "Stack.hpp"
#include <cstdint>
#include <string>

namespace dsa {

    /// @brief Convert a decimal number to any `base` number, and return a stack reference `s`
    /// collecting all characters in reverse order of the converted number.
    /// @param s A stack collection contains characters in reverse order of number to be converted
    /// @param n The decimal number to be converted
    /// @param base The base to be converted
    void decimalConversion(Stack<char> &s, int64_t n, uint8_t base);

    /// @brief Match all pair brackets(include parentheses, square brackets and curly brackets)
    /// of string expression.
    /// @param expr The string expression to be matched
    /// @return If all pairs matched return ture, otherwise false.
    bool matchBrackets(const std::string &expr);
}
