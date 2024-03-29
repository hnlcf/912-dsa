#include <test_header.h>

TEST_CASE("Queue: basic methods", "[queue]") {
  dsa::Queue<int> q;
  q.enqueue(1);

  REQUIRE(q.size() == 1);
  REQUIRE(q.isEmpty() == false);
  REQUIRE(q.first() == 1);
  REQUIRE(q.last() == 1);

  auto tmp = q.dequeue();

  REQUIRE(tmp == 1);
  REQUIRE(q.size() == 0);
  REQUIRE(q.isEmpty() == true);
}
