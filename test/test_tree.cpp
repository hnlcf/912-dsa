#include "BinTree.hpp"
#include "catch2/catch.hpp"

using dsa::BinTree;
using dsa::BinTreeNode;

TEST_CASE("TreeNode: Initialize", "[bin-tree]") {
    dsa::BinTree<int> p;

    REQUIRE(p.root() != nullptr);
    REQUIRE(p.size() == 1);
    REQUIRE(!p.isEmpty());

    p.insertAsRightNode(p.root(), 3);

    REQUIRE(p.size() == 2);
    REQUIRE(p.root()->m_height == 1);
}

template<class T>
struct GetTraverse {
    std::string m_data{};

    void clear() {
        m_data.clear();
    }

    virtual void operator()(T &e) {
        m_data += e;
    }
};


TEST_CASE("TreeNode: Four Traverse", "[bin-tree]") {
    BinTreeNode<char> root('1', nullptr);
    root.insertAsLeftChild('2');
    root.insertAsRightChild('3');

    root.m_left->insertAsLeftChild('5');
    root.m_left->insertAsRightChild('4');
    root.m_right->insertAsRightChild('6');

    root.m_left->m_left->insertAsLeftChild('7');
    root.m_left->m_left->insertAsRightChild('8');
    root.m_right->m_right->insertAsLeftChild('9');

    GetTraverse<char> visit;

    SECTION("TreeNode: preorder traverse") {
        visit.clear();
        root.traversePreorderRecur(&root, visit);
        REQUIRE(visit.m_data == "125784369");

        visit.clear();
        root.traversePreorderIter1(&root, visit);
        REQUIRE(visit.m_data == "125784369");

        visit.clear();
        root.traversePreorderIter2(&root, visit);
        REQUIRE(visit.m_data == "125784369");
    }

    SECTION("TreeNode: inorder traverse") {
        visit.clear();
        root.traverseInorderRecur(&root, visit);
        REQUIRE(visit.m_data == "758241396");

        visit.clear();
        root.traverseInorderIter(&root, visit);
        REQUIRE(visit.m_data == "758241396");
    }

    SECTION("TreeNode: postorder traverse") {
        visit.clear();
        root.traversePostorderRecur(&root, visit);
        REQUIRE(visit.m_data == "785429631");

        visit.clear();
        root.traversePostorderIter(&root, visit);
        REQUIRE(visit.m_data == "785429631");
    }

    SECTION("TreeNode: level traverse") {
        visit.clear();
        root.traverseLevel(&root, visit);
        REQUIRE(visit.m_data == "123546789");
    }
}
