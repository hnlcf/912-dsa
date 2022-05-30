#include "Example/StackExample.h"
#include "catch2/catch.hpp"


TEST_CASE("Match brackets in string", "[stack][example]") {
    SECTION("empty string") {
        std::string s1 = "";
        REQUIRE(dsa::matchBrackets(s1) == true);
    }

    SECTION("round brackets") {
        std::string s2 = "(";
        std::string s3 = ")";
        std::string s4 = "()";

        REQUIRE(dsa::matchBrackets(s2) == false);
        REQUIRE(dsa::matchBrackets(s3) == false);
        REQUIRE(dsa::matchBrackets(s4) == true);
    }

    SECTION("square brackets") {
        std::string s2 = "[";
        std::string s3 = "]";
        std::string s4 = "[]";

        REQUIRE(dsa::matchBrackets(s2) == false);
        REQUIRE(dsa::matchBrackets(s3) == false);
        REQUIRE(dsa::matchBrackets(s4) == true);
    }

    SECTION("braces") {
        std::string s2 = "{";
        std::string s3 = "}";
        std::string s4 = "{}";

        REQUIRE(dsa::matchBrackets(s2) == false);
        REQUIRE(dsa::matchBrackets(s3) == false);
        REQUIRE(dsa::matchBrackets(s4) == true);
    }

    SECTION("expressions") {
        std::string s2 = "int\n"
                         "main() {\n"
                         "    std::cout << \"912-dsa\" << std::endl;\n"
                         "    return 0;\n"
                         "}";

        std::string s3 = "{(()+())+([()-()])}";
        std::string s4 = "{(()+()+([()-()])}";
        REQUIRE(dsa::matchBrackets(s2) == true);
        REQUIRE(dsa::matchBrackets(s3) == true);
        REQUIRE(dsa::matchBrackets(s4) == false);
    }
}

TEST_CASE("Evaluate a math expression", "[stack][example]") {
    SECTION("All operators") {
        std::string str = "(1+2^3!-4)*(5!-(6-(7-(89-0!))))";
        REQUIRE(dsa::evaluate(str) == 2013.0);
    }
    SECTION("+ - operators") {
        std::string str = "1+2-6";
        REQUIRE(dsa::evaluate(str) == -3.0);
    }
    SECTION("* / operators") {
        std::string str = "2*6/3";
        REQUIRE(dsa::evaluate(str) == 4.0);
    }
    SECTION("^ operators") {
        std::string str = "2^3";
        REQUIRE(dsa::evaluate(str)  == 8.0);
    }

    SECTION("! operators") {
        std::string str = "3!-0!";
        REQUIRE(dsa::evaluate(str)  == 5.0);
    }

    SECTION("() operators") {
        std::string str = "4*(3-5)";
        REQUIRE(dsa::evaluate(str)  == -8.0);
    }
}
