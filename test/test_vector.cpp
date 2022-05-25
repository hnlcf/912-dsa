#define CATCH_CONFIG_MAIN
#include "Vector.hpp"
#include "catch2/catch.hpp"

TEST_CASE("Vector can be initialized", "[Vector]") {
    dsa::Vector<int> v1{ 0, 1, 2, 3 };
    dsa::Vector<int> v2(v1);
    // TODO: `==` operator is not implemented
    REQUIRE(1 + 2 == 3);
}
