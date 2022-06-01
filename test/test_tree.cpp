#include "Tree.hpp"
#include "catch2/catch.hpp"

TEST_CASE("TreeNode: Initialize", "[tree]") {
    TreeNode<int> t;

    REQUIRE(t.m_value == 0);
    REQUIRE(t.m_left == nullptr);
    REQUIRE(t.m_right == nullptr);
}
