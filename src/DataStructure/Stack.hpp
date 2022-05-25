#pragma once

#include "IStack.hpp"
#include "Vector.hpp"
#include <cstdint>
#include <string>

namespace dsa {
    template<typename T>
    class Stack : public IStack<T> {
    private:
        Vector<T> *m_vector;

    public:
        Stack() {
            m_vector = new Vector<T>;
        };

        ~Stack() {
            delete m_vector;
            m_vector = nullptr;
        };

        void push(T const &e) override;
        T    pop() override;
        T   &top() override;
        bool isEmpty() override;
    };

    template<typename T>
    void Stack<T>::push(const T &e) {
        m_vector->push_back(e);
    }

    template<typename T>
    T Stack<T>::pop() {
        return m_vector->pop_back();
    }

    template<typename T>
    T &Stack<T>::top() {
        return (*m_vector)[m_vector->size() - 1];
    }

    template<typename T>
    bool Stack<T>::isEmpty() {
        return m_vector->size() == 0;
    }

    /// @brief Convert a decimal number to any `base` number, and return a stack reference `s`
    /// collecting all characters in reverse order of the converted number.
    /// @param s A stack collection contains characters in reverse order of number to be converted
    /// @param n The decimal number to be converted
    /// @param base The base to be converted
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

    /// @brief Match all pair brackets(include parentheses, square brackets and curly brackets)
    /// of string expression.
    /// @param expr The string expression to be matched
    /// @return If all pairs matched return ture, otherwise false.
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
