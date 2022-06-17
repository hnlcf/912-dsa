#include <StackExample.h>

namespace dsa {

    /// @brief Determine if the given character is a number.
    /// @param ch Character given
    /// @return True iff `ch` is a number, otherwise false.
    static inline bool isDigit(char ch);

    /// @brief Read a continuous number from `str[index]`, and store with stack
    /// @param s The stack given for storing number
    /// @param str The string given
    /// @param index The specific position in string
    static void readNumber(Stack<double> &s, const std::string &str, std::size_t &index);

    /// @brief Compare the calculate priorities of TWO operators
    /// @param lhs The operator in left side
    /// @param rhs The operator in right side
    /// @return A `MathOperator::Order` enumerator according to invoke `MathOperator::orderBetweenOperator()`
    static inline MathOperator::Order orderBetween(char lhs, char rhs);

    /// @brief Calculate a math expression with ONE operator(factorial) and ONE operand.
    /// @param opr The operator given
    /// @param opd The UNIQUE operand given
    /// @return Result of calculation
    static double calculate(MathOperator::Opr opr, double opd);

    /// @brief Calculate a math expression with ONE operator and TWO operands.
    /// @param opr The operator given
    /// @param opd1 The first(left) operand given
    /// @param opd2 The second(right) operand given
    /// @return Result of calculation
    static double calculate(MathOperator::Opr opr, double opd1, double opd2);

    void decimalConversion(Stack<char> &s, int64_t n, uint8_t base) {
        const char digits[] = { '0', '1', '2', '3', '4', '5', '6', '7',
                                '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
        if (n == 0) {
            s.push(digits[n]);
        } else {
            bool is_negative = n < 0;
            n = std::abs(n);
            while (n != 0) {
                s.push(digits[n % base]);
                n /= base;
            }
            if (is_negative) {
                s.push('-');
            }
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

    double evaluate(const std::string &exp) {
        Stack<double> operands;
        Stack<char>   operators;
        std::size_t   i = 0;

        operators.push('\0');
        while (!operators.isEmpty()) {
            if (isDigit(exp[i])) {
                readNumber(operands, exp, i);
            } else {
                switch (orderBetween(operators.top(), exp[i])) {
                    case MathOperator::Order::Less: {
                        operators.push(exp[i]);
                        i++;
                        break;
                    }
                    case MathOperator::Order::Equal: {
                        operators.pop();
                        i++;
                        break;
                    }
                    case MathOperator::Order::More: {
                        double tmp;
                        auto   opr = MathOperator::parseOperator(operators.pop());
                        if (opr == MathOperator::Opr::Fac) {
                            double opd = operands.pop();
                            tmp = calculate(opr, opd);
                        } else {
                            double opd2 = operands.pop();
                            double opd1 = operands.pop();
                            tmp = calculate(opr, opd1, opd2);
                        }
                        operands.push(tmp);
                        break;
                    }
                    case MathOperator::Order::None:
                    default:
                        break;
                }
            }
        }
        return operands.pop();
    }

    static inline bool isDigit(char ch) {
        return ((48 <= ch) && (ch <= 57));
    }

    static void readNumber(Stack<double> &s, const std::string &str, std::size_t &index) {
        s.push(str[index] - '0');
        index++;
        while (isDigit(str[index])) {
            s.push(s.pop() * 10 + str[index] - '0');
            index++;
        }
    }

    static inline MathOperator::Order orderBetween(char lhs, char rhs) {
        auto l_opr = MathOperator::parseOperator(lhs);
        auto r_opr = MathOperator::parseOperator(rhs);
        return MathOperator::orderBetweenOperator(l_opr, r_opr);
    }

    static double calculate(MathOperator::Opr opr, double opd) {
        if (opr != MathOperator::Opr::Fac) {
            return MAXFLOAT;
        }
        if (opd == 0.0) {
            return 1.0;
        }
        double ans = opd;
        opd--;
        while (opd > 0) {
            ans *= opd;
            opd--;
        }
        return ans;
    }

    static double calculate(MathOperator::Opr opr, double opd1, double opd2) {
        double ans = 0.0;
        switch (opr) {
            case MathOperator::Opr::Add:
                ans = opd1 + opd2;
                break;
            case MathOperator::Opr::Sub:
                ans = opd1 - opd2;
                break;
            case MathOperator::Opr::Mul:
                ans = opd1 * opd2;
                break;
            case MathOperator::Opr::Div:
                ans = opd1 / opd2;
                break;
            case MathOperator::Opr::Exp:
                ans = std::pow(opd1, opd2);
                break;
            default:
                break;
        }
        return ans;
    }
}
