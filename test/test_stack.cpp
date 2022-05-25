#include "Stack.hpp"
#include "catch2/catch.hpp"


TEST_CASE("Parents in string matched", "[matchParents]") {
    SECTION("empty string") {
        std::string s1 = "";
        REQUIRE(dsa::matchParents(s1) == true);
    }

    SECTION("round brackets") {
        std::string s2 = "(";
        std::string s3 = ")";
        std::string s4 = "()";

        REQUIRE(dsa::matchParents(s2) == false);
        REQUIRE(dsa::matchParents(s3) == false);
        REQUIRE(dsa::matchParents(s4) == true);
    }

    SECTION("square brackets") {
        std::string s2 = "[";
        std::string s3 = "]";
        std::string s4 = "[]";

        REQUIRE(dsa::matchParents(s2) == false);
        REQUIRE(dsa::matchParents(s3) == false);
        REQUIRE(dsa::matchParents(s4) == true);
    }

    SECTION("braces") {
        std::string s2 = "{";
        std::string s3 = "}";
        std::string s4 = "{}";

        REQUIRE(dsa::matchParents(s2) == false);
        REQUIRE(dsa::matchParents(s3) == false);
        REQUIRE(dsa::matchParents(s4) == true);
    }

    SECTION("expressions") {
        std::string s2 = "int\n"
                         "main() {\n"
                         "    std::cout << \"912-dsa\" << std::endl;\n"
                         "    return 0;\n"
                         "}";

        std::string s3 = "{(()+())+([()-()])}";
        std::string s4 = "{(()+()+([()-()])}";
        REQUIRE(dsa::matchParents(s2) == true);
        REQUIRE(dsa::matchParents(s3) == true);
        REQUIRE(dsa::matchParents(s4) == false);
    }
}
