#include "StackExample.h"

namespace dsa {

    void decimalConvertion(Stack<char> &s, int64_t n, uint8_t base) {
        const char digits[] = { '0', '1', '2', '3', '4', '5', '6', '7',
                                '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
        bool       is_negative = n < 0;
        while (n != 0) {
            s.push(digits[n % base]);
            n /= base;
        }
        if (is_negative) {
            s.push('-');
        }
    }

    bool matchBrackets(const std::string &expr) {
        if (expr.empty()) {
            return true;
        }
        Stack<char> s;
        for (const auto &ch: expr) {
            switch (ch) {
                case '(':
                case '[':
                case '{': {
                    s.push(ch);
                    break;
                }
                case ')': {
                    if (s.isEmpty() || s.pop() != '(') {
                        return false;
                    }
                    break;
                }
                case ']': {
                    if (s.isEmpty() || s.pop() != '[') {
                        return false;
                    }
                    break;
                }
                case '}': {
                    if (s.isEmpty() || s.pop() != '{') {
                        return false;
                    }
                    break;
                }
                default:
                    break;
            }
        }
        return s.isEmpty();
    }
}
