#include <stack/stackexample.h>

namespace dsa {

/// @brief Determine if the given character is a number.
/// @param ch Character given
/// @return True iff `ch` is a number, otherwise false.
static inline bool IsDigit(char ch) { return ((48 <= ch) && (ch <= 57)); }

/// @brief Read a continuous number from `str[index]`, and store with stack
/// @param s The stack given for storing number
/// @param str The string given
/// @param index The specific position in string
static void ReadNumber(Stack<double>& s, const std::string& str,
                       std::size_t& index) {
  s.Push(str[index] - '0');
  index++;
  while (IsDigit(str[index])) {
    s.Push(s.Pop() * 10 + str[index] - '0');
    index++;
  }
}

/// @brief Compare the Calculate priorities of TWO operators
/// @param lhs The operator in left side
/// @param rhs The operator in right side
/// @return A `MathOperator::Order` enumerator according to invoke
/// `MathOperator::OrderBetweenOperator()`
static inline MathOperator::Order OrderBetween(char lhs, char rhs) {
  auto l_opr = MathOperator::ParseOperator(lhs);
  auto r_opr = MathOperator::ParseOperator(rhs);
  return MathOperator::OrderBetweenOperator(l_opr, r_opr);
}

/// @brief Calculate a math expression with ONE operator(factorial) and ONE
/// operand.
/// @param opr The operator given
/// @param opd The UNIQUE operand given
/// @return Result of calculation
static double Calculate(MathOperator::Opr opr, double opd) {
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

/// @brief Calculate a math expression with ONE operator and TWO operands.
/// @param opr The operator given
/// @param opd1 The First(left) operand given
/// @param opd2 The second(right) operand given
/// @return Result of calculation
static double Calculate(MathOperator::Opr opr, double opd1, double opd2) {
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

void DecimalConversion(Stack<char>& s, int64_t n, uint8_t base) {
  const char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                         '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
  if (n == 0) {
    s.Push(digits[n]);
  } else {
    bool is_negative = n < 0;
    n = std::abs(n);
    while (n != 0) {
      s.Push(digits[n % base]);
      n /= base;
    }
    if (is_negative) {
      s.Push('-');
    }
  }
}

bool MatchBrackets(const std::string& expr) {
  if (expr.empty()) {
    return true;
  }
  Stack<char> s;
  for (const auto& ch : expr) {
    switch (ch) {
      case '(':
      case '[':
      case '{': {
        s.Push(ch);
        break;
      }
      case ')': {
        if (s.IsEmpty() || s.Pop() != '(') {
          return false;
        }
        break;
      }
      case ']': {
        if (s.IsEmpty() || s.Pop() != '[') {
          return false;
        }
        break;
      }
      case '}': {
        if (s.IsEmpty() || s.Pop() != '{') {
          return false;
        }
        break;
      }
      default:
        break;
    }
  }
  return s.IsEmpty();
}

double Evaluate(const std::string& exp) {
  Stack<double> operands;
  Stack<char> operators;
  std::size_t i = 0;

  operators.Push('\0');
  while (!operators.IsEmpty()) {
    if (IsDigit(exp[i])) {
      ReadNumber(operands, exp, i);
    } else {
      switch (OrderBetween(operators.Top(), exp[i])) {
        case MathOperator::Order::Less: {
          operators.Push(exp[i]);
          i++;
          break;
        }
        case MathOperator::Order::Equal: {
          operators.Pop();
          i++;
          break;
        }
        case MathOperator::Order::More: {
          double tmp;
          auto opr = MathOperator::ParseOperator(operators.Pop());
          if (opr == MathOperator::Opr::Fac) {
            double opd = operands.Pop();
            tmp = Calculate(opr, opd);
          } else {
            double opd2 = operands.Pop();
            double opd1 = operands.Pop();
            tmp = Calculate(opr, opd1, opd2);
          }
          operands.Push(tmp);
          break;
        }
        case MathOperator::Order::None:
        default:
          break;
      }
    }
  }
  return operands.Pop();
}

}  // namespace dsa
