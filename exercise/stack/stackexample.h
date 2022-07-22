#ifndef INC_912_DSA_EXERCISE_STACK_STACKEXAMPLE_H_
#define INC_912_DSA_EXERCISE_STACK_STACKEXAMPLE_H_

#include <ds/stack.h>

#include <cmath>
#include <cstdint>
#include <string>

namespace dsa {

/// @brief Convert a decimal number to any `base` number, and return a stack
/// reference `s` collecting all characters in reverse order of the converted
/// number.
/// @param s A stack collection contains characters in reverse order of number
/// to be converted
/// @param n The decimal number to be converted
/// @param base The base to be converted
void decimalConversion(Stack<char>& s, int64_t n, uint8_t base);

/// @brief Match all pair brackets(include parentheses, square brackets and
/// curly brackets) of string expression.
/// @param expr The string expression to be matched
/// @return If all pairs matched return ture, otherwise false.
bool matchBrackets(const std::string& expr);

/// @brief Compute a math expression
/// @param exp The math expression given
/// @return Result of math expression
double evaluate(const std::string& exp);

/// @brief Define the math operators with corresponding orders of priority.
struct MathOperator {
  enum class Opr : uint32_t {
    None = 0xffff,
    Add = 0x0001,           /// `+`
    Sub = 0x0002,           /// `-`
    Mul = 0x0011,           /// `*`
    Div = 0x0012,           /// `/`
    Exp = 0x0101,           /// `^`
    Fac = 0x0102,           /// `!`
    LeftBracket = 0x1001,   /// `(`
    RightBracket = 0x1002,  /// `)`
    Eof = 0x00,             /// `\0`
  };

  enum class Order : uint8_t {
    None = 0x00,   /// ` `, the blank
    Less = 0x01,   /// `<`
    More = 0x02,   /// `>`
    Equal = 0x04,  /// `=`
  };

  /// @brief Convert a character to corresponding math operator.
  static Opr parseOperator(const char ch) {
    Opr opr = Opr::None;
    switch (ch) {
      case '+':
        opr = Opr::Add;
        break;
      case '-':
        opr = Opr::Sub;
        break;
      case '*':
        opr = Opr::Mul;
        break;
      case '/':
        opr = Opr::Div;
        break;
      case '^':
        opr = Opr::Exp;
        break;
      case '!':
        opr = Opr::Fac;
        break;
      case '(':
        opr = Opr::LeftBracket;
        break;
      case ')':
        opr = Opr::RightBracket;
        break;
      case '\0':
        opr = Opr::Eof;
        break;
      default:
        break;
    }
    return opr;
  }

  /// @brief Compare the order of two math operators according to priorities.
  /// @param lhs Left operator
  /// @param rhs Right operator
  /// @return The enumeration member corresponding to order.
  static Order orderBetweenOperator(const MathOperator::Opr& lhs,
                                    const MathOperator::Opr& rhs) {
    Order ans = Order::None;
    switch (lhs) {
      case Opr::Add:
      case Opr::Sub: {
        switch (rhs) {
          case Opr::Add:
          case Opr::Sub:
          case Opr::RightBracket:
          case Opr::Eof:
            ans = Order::More;
            break;
          case Opr::Mul:
          case Opr::Div:
          case Opr::Exp:
          case Opr::Fac:
          case Opr::LeftBracket:
            ans = Order::Less;
            break;
          default:
            break;
        }
        break;
      }
      case Opr::Mul:
      case Opr::Div: {
        switch (rhs) {
          case Opr::Add:
          case Opr::Sub:
          case Opr::Mul:
          case Opr::Div:
          case Opr::RightBracket:
          case Opr::Eof:
            ans = Order::More;
            break;
          case Opr::Exp:
          case Opr::Fac:
          case Opr::LeftBracket:
            ans = Order::Less;
            break;
          default:
            break;
        }
        break;
      }
      case Opr::Exp: {
        switch (rhs) {
          case Opr::Add:
          case Opr::Sub:
          case Opr::Mul:
          case Opr::Div:
          case Opr::Exp:
          case Opr::RightBracket:
          case Opr::Eof:
            ans = Order::More;
            break;
          case Opr::Fac:
          case Opr::LeftBracket:
            ans = Order::Less;
            break;
          default:
            break;
        }
        break;
      }
      case Opr::Fac: {
        switch (rhs) {
          case Opr::Add:
          case Opr::Sub:
          case Opr::Mul:
          case Opr::Div:
          case Opr::Exp:
          case Opr::Fac:
          case Opr::RightBracket:
          case Opr::Eof:
            ans = Order::More;
            break;
          case Opr::LeftBracket:
            ans = Order::None;
            break;
          default:
            break;
        }
        break;
      }
      case Opr::LeftBracket: {
        switch (rhs) {
          case Opr::Add:
          case Opr::Sub:
          case Opr::Mul:
          case Opr::Div:
          case Opr::Exp:
          case Opr::Fac:
          case Opr::LeftBracket:
            ans = Order::Less;
            break;
          case Opr::RightBracket:
            ans = Order::Equal;
            break;
          case Opr::Eof:
            ans = Order::More;
            break;
          default:
            break;
        }
        break;
      }
      case Opr::RightBracket: {
        ans = Order::None;
        break;
      }
      case Opr::Eof: {
        switch (rhs) {
          case Opr::Add:
          case Opr::Sub:
          case Opr::Mul:
          case Opr::Div:
          case Opr::Exp:
          case Opr::Fac:
          case Opr::LeftBracket:
            ans = Order::Less;
            break;
          case Opr::RightBracket:
            ans = Order::None;
            break;
          case Opr::Eof:
            ans = Order::Equal;
            break;
          default:
            break;
        }
      }
      case Opr::None:
      default:
        break;
    }
    return ans;
  }
};
}  // namespace dsa

#endif