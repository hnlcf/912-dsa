#include "List.hpp"
#include "catch2/catch.hpp"

TEST_CASE("List initialize", "[List]") {
    SECTION("empty list") {
        dsa::List<int> l;
        REQUIRE(l.size() == 0);
        REQUIRE(l.first() == l.last()->m_succ);
        REQUIRE(l.last() == l.first()->m_pred);
    }
}
