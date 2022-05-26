#define CATCH_CONFIG_MAIN
#include "Vector.hpp"
#include "catch2/catch.hpp"

TEST_CASE("Vector initialize", "[Vector]") {
    dsa::Vector<int> v1{ 0, 1, 2, 3 };
    dsa::Vector<int> v2(v1);
    // TODO: `==` operator is not implemented
    REQUIRE(v1.size() == v2.size());
    for (int i = 0; i < v1.size(); ++i) {
        REQUIRE(v1[i] == v2[i]);
    }
}
