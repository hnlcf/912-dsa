#include <BinTree.hpp>
#include <catch2/catch_test_macros.hpp>

using dsa::BinTree;
using dsa::BinTreeNode;

TEST_CASE("BinTreeNode: [Constructor]", "[bin-tree]") {
    SECTION("BinTreeNode: Empty Constructor") {
        BinTreeNode<int> p;

        REQUIRE(p.m_data == 0);
        REQUIRE(p.m_height == 0);
        REQUIRE(p.m_parent == nullptr);
        REQUIRE(p.m_left == nullptr);
        REQUIRE(p.m_right == nullptr);
        REQUIRE(p.size() == 1);
    }

    SECTION("BinTreeNode: Construct with data and parent") {
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

        auto *tmp = p.insertAsLeftChild(99);
        REQUIRE(p.m_left->m_data == 99);
        REQUIRE(tmp == p.m_left);
        REQUIRE(p.size() == 2);

        p.insertAsLeftChild(-99);
        REQUIRE(p.m_left->m_data == -99);
        REQUIRE(tmp == p.m_left);
        REQUIRE(p.size() == 2);
    }

    SECTION("BinTreeNode: Insert right") {
        BinTreeNode<int> p;

        REQUIRE(p.m_right == nullptr);

        auto *tmp = p.insertAsRightChild(99);
        REQUIRE(p.m_right->m_data == 99);
        REQUIRE(tmp == p.m_right);
        REQUIRE(p.size() == 2);

        p.insertAsRightChild(-99);
        REQUIRE(p.m_right->m_data == -99);
        REQUIRE(tmp == p.m_right);
        REQUIRE(p.size() == 2);
    }

    SECTION("BinTreeNode: Insert both left and right") {
        BinTreeNode<int> p;

        auto *tmp1 = p.insertAsLeftChild(1);
        auto *tmp2 = p.insertAsRightChild(-1);

        REQUIRE(p.m_left->m_data == 1);
        REQUIRE(p.m_right->m_data == -1);
        REQUIRE(tmp1 == p.m_left);
        REQUIRE(tmp2 == p.m_right);
        REQUIRE(p.size() == 3);

        p.insertAsLeftChild(-99);
        p.insertAsRightChild(99);
        REQUIRE(p.m_left->m_data == -99);
        REQUIRE(p.m_right->m_data == 99);
        REQUIRE(tmp1 == p.m_left);
        REQUIRE(tmp2 == p.m_right);
    }
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


TEST_CASE("BinTreeNode: [Four Traverse]", "[bin-tree]") {
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

    SECTION("BinTreeNode: Preorder traverse") {
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

    SECTION("BinTreeNode: Inorder traverse") {
        visit.clear();
        root.traverseInorderRecur(&root, visit);
        REQUIRE(visit.m_data == "758241396");

        visit.clear();
        root.traverseInorderIter(&root, visit);
        REQUIRE(visit.m_data == "758241396");
    }

    SECTION("BinTreeNode: Postorder traverse") {
        visit.clear();
        root.traversePostorderRecur(&root, visit);
        REQUIRE(visit.m_data == "785429631");

        visit.clear();
        root.traversePostorderIter(&root, visit);
        REQUIRE(visit.m_data == "785429631");
    }

    SECTION("BinTreeNode: Level traverse") {
        visit.clear();
        root.traverseLevel(&root, visit);
        REQUIRE(visit.m_data == "123546789");
    }
}

TEST_CASE("BinTree: [Constructor]", "[bin-tree]") {
    SECTION("BinTree: Empty construct") {
        BinTree<int> p;
        REQUIRE(p.size() == 0);
        REQUIRE(p.root() == nullptr);
    }

    SECTION("BinTree: Construct with root") {
        BinTree<int> p;

        p.insertRoot(99);
        REQUIRE(p.size() == 1);
        REQUIRE(p.root() != nullptr);
        REQUIRE(p.root()->m_data == 99);
    }
}
