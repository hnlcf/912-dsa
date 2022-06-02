#include "BinTree.hpp"
#include "catch2/catch.hpp"

TEST_CASE("TreeNode: Initialize", "[bin-tree]") {
    dsa::BinTree<int> p;

    REQUIRE(p.root() != nullptr);
    REQUIRE(p.size() == 1);
    REQUIRE(!p.isEmpty());

    p.insert(p.root(), 3);

    REQUIRE(p.size() == 2);
}
