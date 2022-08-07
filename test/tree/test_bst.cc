#include <test_header.h>

using dsa::BST;
using dsa::Vector;

TEST_CASE("BST: Insert", "[bst]") {
  BST<int> b;

  b.insert(0);
  b.insert(25);
  b.insert(-99);
  b.insert(5182);
  b.insert(3);
  b.insert(-391);

  REQUIRE(b.size() == 6);
}

TEST_CASE("BST: traverse", "[bst]") {
  BST<int> b;
  b.insert(0);
  b.insert(25);
  b.insert(-99);
  b.insert(5182);
  b.insert(3);
  b.insert(-391);

  GetTraverse<int> visit;

  SECTION("traverse inorder") {
    visit.clear();
    b.traverseInorder(visit);

    Vector<int> actual = visit.data();

    Vector<int> expect = {-391, -99, 0, 3, 25, 5182};

    REQUIRE(actual == expect);
  }
}
