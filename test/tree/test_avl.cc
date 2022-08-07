#include <test_header.h>

using dsa::AVL;
using dsa::Vector;

TEST_CASE("AVL: basic", "[bst][avl]") {
  AVL<int> a;

  a.insert(9999);
  a.insert(99);
  a.insert(27);
  a.insert(1);
  a.insert(0);
  a.insert(-3);
  a.insert(-54);

  REQUIRE(a.size() == 7);

  GetTraverse<int> visit;

  SECTION("traverse AVL in-order") {
    visit.clear();
    a.traverseInorder(visit);

    Vector<int> actual = visit.data();
    Vector<int> expect = {-54, -3, 0, 1, 27, 99, 9999};

    REQUIRE(actual == expect);
  }
}
