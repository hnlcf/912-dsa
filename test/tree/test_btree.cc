#include <test_header.h>

using dsa::BTree;

TEST_CASE("BTree: Initialize", "[bst][btree]") {
  BTree<int> b;
  REQUIRE(1 + 1 == 2);
}