#include <test_header.h>

using dsa::AVL;
using dsa::Vector;

TEST_CASE("AVL: basic", "[bst][avl]") {
  AVL<int> a;

  a.Insert(9999);
  a.Insert(99);
  a.Insert(27);
  a.Insert(1);
  a.Insert(0);
  a.Insert(-3);
  a.Insert(-54);

  REQUIRE(a.Size() == 7);

  GetTraverse<int> visit;

  SECTION("Traverse AVL in-order") {
    visit.Clear();
    a.TraverseInorder(visit);

    Vector<int> actual = visit.Data();
    Vector<int> expect = {-54, -3, 0, 1, 27, 99, 9999};

    REQUIRE(actual == expect);
  }
}
