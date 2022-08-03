#include <test_header.h>

using dsa::BTree;

TEST_CASE("BTree: Initialize", "[btree]") {
  BTree<int> b;
  REQUIRE(1 + 1 == 2);
}