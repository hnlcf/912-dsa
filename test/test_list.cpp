#include "List.hpp"
#include "catch2/catch.hpp"

TEST_CASE("List can be initialized", "[List]") {
    SECTION("empty list") {
        dsa::List<int> l;
        REQUIRE(l.size() == 1);
        REQUIRE(l.first() == l.last()->m_succ);
        REQUIRE(l.last() == l.first()->m_pred);
    }
}
