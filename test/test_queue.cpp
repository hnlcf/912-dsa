#include "Queue.hpp"
#include "catch2/catch.hpp"

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

    auto f = q.first();
    auto l = q.last();
    REQUIRE_FALSE(f == -1);
    REQUIRE_FALSE(l == -1);
}
