#include <test_header.h>

using dsa::BinTree;
using dsa::BinTreeNode;
using dsa::Vector;

TEST_CASE("BinTreeNode: [Constructor]", "[bin-tree]") {
  SECTION("BinTreeNode: Empty Constructor") {
    BinTreeNode<int> p;

    REQUIRE(p.m_data == 0);
    REQUIRE(p.m_height == 0);
    REQUIRE(p.m_parent == nullptr);
    REQUIRE(p.m_left == nullptr);
    REQUIRE(p.m_right == nullptr);
    REQUIRE(p.Size() == 1);
  }

  SECTION("BinTreeNode: Construct with data and GetParent") {
    BinTreeNode<int> p(-1, nullptr);

    REQUIRE(p.m_data == -1);
    REQUIRE(p.m_height == 0);
    REQUIRE(p.m_parent == nullptr);
    REQUIRE(p.m_left == nullptr);
    REQUIRE(p.m_right == nullptr);
  }

  SECTION("BinTreeNode: Construct with all fields") {
    BinTreeNode<int> p(99, 0, nullptr, nullptr, nullptr);

    REQUIRE(p.m_data == 99);
    REQUIRE(p.m_height == 0);
    REQUIRE(p.m_parent == nullptr);
    REQUIRE(p.m_left == nullptr);
    REQUIRE(p.m_right == nullptr);
  }
}

TEST_CASE("BinTreeNode: [Insert Node]", "[bin-tree]") {
  SECTION("BinTreeNode: Insert left") {
    BinTreeNode<int> p;

    REQUIRE(p.m_left == nullptr);

    auto* tmp = p.InsertAsLeftChild(99);
    REQUIRE(p.m_left->m_data == 99);
    REQUIRE(tmp == p.m_left);
    REQUIRE(p.Size() == 2);

    p.InsertAsLeftChild(-99);
    REQUIRE(p.m_left->m_data == -99);
    REQUIRE(tmp == p.m_left);
    REQUIRE(p.Size() == 2);
  }

  SECTION("BinTreeNode: Insert right") {
    BinTreeNode<int> p;

    REQUIRE(p.m_right == nullptr);

    auto* tmp = p.InsertAsRightChild(99);
    REQUIRE(p.m_right->m_data == 99);
    REQUIRE(tmp == p.m_right);
    REQUIRE(p.Size() == 2);

    p.InsertAsRightChild(-99);
    REQUIRE(p.m_right->m_data == -99);
    REQUIRE(tmp == p.m_right);
    REQUIRE(p.Size() == 2);
  }

  SECTION("BinTreeNode: Insert both left and right") {
    BinTreeNode<int> p;

    auto* tmp1 = p.InsertAsLeftChild(1);
    auto* tmp2 = p.InsertAsRightChild(-1);

    REQUIRE(p.m_left->m_data == 1);
    REQUIRE(p.m_right->m_data == -1);
    REQUIRE(tmp1 == p.m_left);
    REQUIRE(tmp2 == p.m_right);
    REQUIRE(p.Size() == 3);

    p.InsertAsLeftChild(-99);
    p.InsertAsRightChild(99);
    REQUIRE(p.m_left->m_data == -99);
    REQUIRE(p.m_right->m_data == 99);
    REQUIRE(tmp1 == p.m_left);
    REQUIRE(tmp2 == p.m_right);
  }
}

TEST_CASE("BinTreeNode: [Four Traverse]", "[bin-tree]") {
  BinTreeNode<int> root(1, nullptr);
  root.InsertAsLeftChild(2);
  root.InsertAsRightChild(3);

  root.m_left->InsertAsLeftChild(5);
  root.m_left->InsertAsRightChild(4);
  root.m_right->InsertAsRightChild(6);

  root.m_left->m_left->InsertAsLeftChild(7);
  root.m_left->m_left->InsertAsRightChild(8);
  root.m_right->m_right->InsertAsLeftChild(9);

  GetTraverse<int> visit;

  SECTION("BinTreeNode: Preorder Traverse") {
    SECTION("Recursive") {
      visit.Clear();
      root.TraversePreorderRecur(&root, visit);

      Vector<int> actual = visit.m_data;
      Vector<int> expect = {1, 2, 5, 7, 8, 4, 3, 6, 9};
      REQUIRE(actual == expect);
    }

    SECTION("Iterative1") {
      visit.Clear();
      root.TraversePreorderIter1(&root, visit);
      Vector<int> actual = visit.m_data;
      Vector<int> expect = {1, 2, 5, 7, 8, 4, 3, 6, 9};
      REQUIRE(actual == expect);
    }

    SECTION("Iterative2") {
      visit.Clear();
      root.TraversePreorderIter2(&root, visit);
      Vector<int> actual = visit.m_data;
      Vector<int> expect = {1, 2, 5, 7, 8, 4, 3, 6, 9};
      REQUIRE(actual == expect);
    }
  }

  SECTION("BinTreeNode: Inorder Traverse") {
    SECTION("Recursive") {
      visit.Clear();
      root.TraverseInorderRecur(&root, visit);
      Vector<int> actual = visit.m_data;
      Vector<int> expect = {7, 5, 8, 2, 4, 1, 3, 9, 6};
      REQUIRE(actual == expect);
    }

    SECTION("Iterative") {
      visit.Clear();
      root.TraverseInorderIter(&root, visit);
      Vector<int> actual = visit.m_data;
      Vector<int> expect = {7, 5, 8, 2, 4, 1, 3, 9, 6};
      REQUIRE(actual == expect);
    }
  }

  SECTION("BinTreeNode: Postorder Traverse") {
    SECTION("Recursive") {
      visit.Clear();
      root.TraversePostorderRecur(&root, visit);
      Vector<int> actual = visit.m_data;
      Vector<int> expect = {7, 8, 5, 4, 2, 9, 6, 3, 1};
      REQUIRE(actual == expect);
    }
    SECTION("Iterative") {
      visit.Clear();
      root.TraversePostorderIter(&root, visit);
      Vector<int> actual = visit.m_data;
      Vector<int> expect = {7, 8, 5, 4, 2, 9, 6, 3, 1};
      REQUIRE(actual == expect);
    }
  }

  SECTION("BinTreeNode: Level Traverse") {
    visit.Clear();
    root.TraverseLevel(&root, visit);
    Vector<int> actual = visit.m_data;
    Vector<int> expect = {1, 2, 3, 5, 4, 6, 7, 8, 9};
    REQUIRE(actual == expect);
  }
}

TEST_CASE("BinTree: [Constructor]", "[bin-tree]") {
  SECTION("BinTree: Empty construct") {
    BinTree<int> p;
    REQUIRE(p.Size() == 0);
    REQUIRE(p.Root() == nullptr);
  }

  SECTION("BinTree: Construct with root") {
    BinTree<int> p;

    p.InsertRoot(99);
    REQUIRE(p.Size() == 1);
    REQUIRE(p.Root() != nullptr);
    REQUIRE(p.Root()->m_data == 99);
  }
}
