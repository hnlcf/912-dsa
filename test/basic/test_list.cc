#include <test_header.h>

TEST_CASE("List initialize", "[list]") {
  SECTION("empty list") {
    dsa::List<int> l;
    REQUIRE(l.size() == 0);
    REQUIRE(l.first() == l.last()->m_succ);
    REQUIRE(l.last() == l.first()->m_pred);
  }
}
