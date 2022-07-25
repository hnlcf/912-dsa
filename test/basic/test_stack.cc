#include <test_header.h>

using dsa::DecimalConversion;
using dsa::Evaluate;
using dsa::MatchBrackets;
using dsa::Stack;

std::string test_decimalConversion(int64_t n, uint8_t base) {
  Stack<char> s;
  DecimalConversion(s, n, base);

  std::string ans;
  while (!s.IsEmpty()) {
    ans += s.Pop();
  }

  return ans;
}

TEST_CASE("Convert decimal number to other base", "[stack][example]") {
  SECTION("Convert 10 to 16") {
    std::string actual;
    std::string expect = "48";
    actual = test_decimalConversion(72, 16);
    REQUIRE(expect == actual);

    actual = test_decimalConversion(-72, 16);
    expect = "-48";
    REQUIRE(expect == actual);

    actual = test_decimalConversion(0, 16);
    expect = "0";
    REQUIRE(expect == actual);
  }

  SECTION("Convert 10 to 8") {
    std::string actual;
    std::string expect = "110";
    actual = test_decimalConversion(72, 8);
    REQUIRE(expect == actual);

    actual = test_decimalConversion(-72, 8);
    expect = "-110";
    REQUIRE(expect == actual);

    actual = test_decimalConversion(0, 8);
    expect = "0";
    REQUIRE(expect == actual);
  }

  SECTION("Convert 10 to 2") {
    std::string actual;
    std::string expect = "1001000";
    actual = test_decimalConversion(72, 2);
    REQUIRE(expect == actual);

    actual = test_decimalConversion(-72, 2);
    expect = "-1001000";
    REQUIRE(expect == actual);

    actual = test_decimalConversion(0, 2);
    expect = "0";
    REQUIRE(expect == actual);
  }
}

TEST_CASE("Match brackets in string", "[stack][example]") {
  SECTION("empty string") {
    std::string s1;
    REQUIRE(MatchBrackets(s1) == true);
  }

  SECTION("round brackets") {
    std::string s2 = "(";
    std::string s3 = ")";
    std::string s4 = "()";

    REQUIRE(MatchBrackets(s2) == false);
    REQUIRE(MatchBrackets(s3) == false);
    REQUIRE(MatchBrackets(s4) == true);
  }

  SECTION("square brackets") {
    std::string s2 = "[";
    std::string s3 = "]";
    std::string s4 = "[]";

    REQUIRE(MatchBrackets(s2) == false);
    REQUIRE(MatchBrackets(s3) == false);
    REQUIRE(MatchBrackets(s4) == true);
  }

  SECTION("braces") {
    std::string s2 = "{";
    std::string s3 = "}";
    std::string s4 = "{}";

    REQUIRE(MatchBrackets(s2) == false);
    REQUIRE(MatchBrackets(s3) == false);
    REQUIRE(MatchBrackets(s4) == true);
  }

  SECTION("expressions") {
    std::string s2 =
        "int\n"
        "main() {\n"
        "    std::cout << \"912-dsa\" << std::endl;\n"
        "    return 0;\n"
        "}";

    std::string s3 = "{(()+())+([()-()])}";
    std::string s4 = "{(()+()+([()-()])}";
    REQUIRE(MatchBrackets(s2) == true);
    REQUIRE(MatchBrackets(s3) == true);
    REQUIRE(MatchBrackets(s4) == false);
  }
}

TEST_CASE("Evaluate a math expression", "[stack][example]") {
  SECTION("All operators") {
    std::string str = "(1+2^3!-4)*(5!-(6-(7-(89-0!))))";
    REQUIRE(Evaluate(str) == 2013.0);

    str = "((0!+1)*(2^(3!+4))+9-(5/((6!*7)/8!)))";
    REQUIRE(Evaluate(str) == 2017.0);
  }
  SECTION("+ - operators") {
    std::string str = "1+2-6";
    REQUIRE(Evaluate(str) == -3.0);
  }
  SECTION("* / operators") {
    std::string str = "2*6/3";
    REQUIRE(Evaluate(str) == 4.0);
  }
  SECTION("^ operators") {
    std::string str = "2^3";
    REQUIRE(Evaluate(str) == 8.0);
  }

  SECTION("! operators") {
    std::string str = "3!-0!";
    REQUIRE(Evaluate(str) == 5.0);
  }

  SECTION("() operators") {
    std::string str = "4*(3-5)";
    REQUIRE(Evaluate(str) == -8.0);
  }
}
