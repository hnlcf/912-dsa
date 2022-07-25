#include <test_header.h>

TEST_CASE("Queue: basic methods", "[queue]") {
  dsa::Queue<int> q;
  q.Enqueue(1);

  REQUIRE(q.Size() == 1);
  REQUIRE(q.IsEmpty() == false);
  REQUIRE(q.First() == 1);
  REQUIRE(q.Last() == 1);

  auto tmp = q.Dequeue();

  REQUIRE(tmp == 1);
  REQUIRE(q.Size() == 0);
  REQUIRE(q.IsEmpty() == true);

  auto f = q.First();
  auto l = q.Last();
  REQUIRE_FALSE(f == -1);
  REQUIRE_FALSE(l == -1);
}
