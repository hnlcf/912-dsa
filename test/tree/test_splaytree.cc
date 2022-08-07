#include <test_header.h>

using dsa::SplayTree;
using dsa::Vector;

TEST_CASE("splay: demo", "[bst][splay]") {
  SplayTree<int> s;

  s.insert(9999);
  s.insert(99);
  s.insert(27);
  s.insert(1);
  s.insert(0);
  s.insert(-3);
  s.insert(-54);

  GetTraverse<int> visit;

  visit.clear();
  s.traverseInorder(visit);

  s.search(1);
  Vector<int> actual = visit.data();

  Vector<int> expect = {-54, -3, 0, 1, 27, 99, 9999};

  REQUIRE(actual == expect);
}
