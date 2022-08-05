#include <test_header.h>

using dsa::SplayTree;
using dsa::Vector;

TEST_CASE("Splay: demo", "[bst][Splay]") {
  SplayTree<int> s;

  s.Insert(9999);
  s.Insert(99);
  s.Insert(27);
  s.Insert(1);
  s.Insert(0);
  s.Insert(-3);
  s.Insert(-54);

  GetTraverse<int> visit;

  visit.Clear();
  s.TraverseInorder(visit);

  s.Search(1);
  Vector<int> actual = visit.Data();

  Vector<int> expect = {-54, -3, 0, 1, 27, 99, 9999};

  REQUIRE(actual == expect);
}
