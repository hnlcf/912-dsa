#include <test_header.h>

TEST_CASE("List initialize", "[list]") {
  SECTION("empty list") {
    dsa::List<int> l;
    REQUIRE(l.Size() == 0);
    REQUIRE(l.First() == l.Last()->m_succ);
    REQUIRE(l.Last() == l.First()->m_pred);
  }
}
