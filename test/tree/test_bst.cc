#include <test_header.h>

using dsa::BST;
using dsa::Vector;

TEST_CASE("BST: Insert", "[bst]") {
  BST<int> b;

  b.Insert(0);
  b.Insert(25);
  b.Insert(-99);
  b.Insert(5182);
  b.Insert(3);
  b.Insert(-391);

  REQUIRE(b.Size() == 6);
}

TEST_CASE("BST: Traverse", "[bst]") {
  BST<int> b;
  b.Insert(0);
  b.Insert(25);
  b.Insert(-99);
  b.Insert(5182);
  b.Insert(3);
  b.Insert(-391);

  GetTraverse<int> visit;

  SECTION("Traverse inorder") {
    visit.Clear();
    b.TraverseInorder(visit);

    Vector<int> actual = visit.Data();

    Vector<int> expect = {-391, -99, 0, 3, 25, 5182};

    REQUIRE(actual == expect);
  }
}
