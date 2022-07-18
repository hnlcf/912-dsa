/// BST -- Binary Search Tree
#ifndef INC_912_DSA_DS_BST_H_
#define INC_912_DSA_DS_BST_H_

#include "autoheader.h"
#include "bintree.h"
#include "entry.h"

namespace dsa {
template <class T>
class BST : public Bintree<T> {
  using Node = BinTreeNode<T>*;
  using Tree = Bintree<T>*;

 private:
  Node m_hot;  // the parent(father) node of the currently visited node

  /// @brief Connect three tree nodes and four subtrees as "3 + 4"
  /// structures(in-order).
  Node
  connect34(Node v1, Node v2, Node v3, Node t1, Node t2, Node t3, Node t4) {
    v1->m_left = t1;
    v1->m_right = t2;
    v1->m_parent = v2;
    if (t1 != nullptr) {
      t1->m_parent = v1;
    }
    if (t2 != nullptr) {
      t2->m_parent = v1;
    }
    this->updateHeightAbove(v1);

    v3->m_left = t3;
    v3->m_right = t4;
    v3->m_parent = v2;
    if (t3 != nullptr) {
      t3->m_parent = v3;
    }
    if (t4 != nullptr) {
      t4->m_parent = v3;
    }
    this->updateHeightAbove(v3);

    v2->m_left = v1;
    v2->m_right = v3;
    this->updateHeightAbove(v2);

    return v2;
  }


 public:
  /// @brief Find the key `e` in BST.
  virtual Node& search(T const& e) {
    m_hot = nullptr;
    return searchInIter(this->m_root, e, m_hot);
  }

  /// @brief Insert the key `e` in BST.
  virtual Node insert(T const& e) {
    auto& target = search(e);
    if (target != nullptr) {
      return target;
    }

    target = new BinTreeNode<T>(e, m_hot);

    this->m_size++;
    this->updateHeightAbove(target);

    return target;
  }

  /// @brief Delete the key `e` from BST.
  virtual bool remove(T const& e) {
    auto& target = search(e);
    if (target == nullptr) {
      return false;
    }

    removeAt(target, m_hot);

    this->m_size--;
    this->updateHeightAbove(m_hot);

    return true;
  }

 public:
  /// @brief [Recursive version] Find the key `e` in BST subtree rooted at node `v`.
  /// @param v The reference of root node of subtree.
  /// @param e The key need to be find.
  /// @param hot The parent(father) node of the currently visited node.
  static Node& searchInRecur(Node& v, T const& e, Node& hot) {
    if ((v == nullptr) || (e == v->m_data)) {
      return v;
    }

    hot = v;

    if (e < v->m_data) {
      return searchInRecur(v->m_left, e, hot);
    } else {
      return searchInRecur(v->m_right, e, hot);
    }
  }

  /// @brief [Iterative version] Find the key `e` in BST subtree rooted at node `v`.
  /// @param v The reference of root node of subtree.
  /// @param e The key need to be find.
  /// @param hot The parent(father) node of the currently visited node.
  static Node& searchInIter(Node& v, T const& e, Node& hot) {
    if ((v == nullptr) || (e == v->m_data)) {
      return v;
    }

    hot = v;

    while (true) {
      auto& p = (e < v->m_data) ? v->m_left : v->m_right;

      if ((p == nullptr) || (e == p->m_data)) {
        return p;
      }

      hot = p;
    }
  }

  /// @brief Remove node `p`. (Use for AVL, Splay, RedBlack...)
  /// @param p The reference of tree node to be deleted, must not nullptr.
  /// @param hot The reference of parent(father) node of `p`, may be nullptr.
  /// @return A tree node pointer which is the successor of `p`, may be nullptr.
  static Node removeAt(Node& p, Node& hot) {
    Node target = p;
    Node succ = nullptr;

    if (p->m_left == nullptr) {
      // Only right child exists
      p = p->m_right;
      succ = p;
    } else if (p->m_right == nullptr) {
      // Only left child exists
      p = p->m_left;
      succ = p;
    } else {
      // The left child and right child both exist

      // find the successor node, because node `p` and its successor node are
      // adjacent in inorder.
      target = target->successor();

      // swap datas stored in `p` ans its successor.
      std::swap(p->m_data, target->m_data);

      // As current `target` is the direct successor of `p`,
      // so `target` must have not left child.
      succ = target->m_right;

      // Create connection from parent to child.
      // After exchange, determine whether node `p` and its successor are
      // adjacent or not.
      if (target->m_parent == p) {
        // If adjacent, the `succ` is the right child of `p`.
        target->m_parent->m_right = succ;
      } else {
        // If not, the `succ` is the right child of `target` and `target` is the
        // left child of its parent, so `succ` should connect to the left child
        // of parent of `target`.
        target->m_parent->m_left = succ;
      }
    }

    // Create connection from child to parent.
    hot = target->m_parent;
    if (succ != nullptr) {
      succ->m_parent = hot;
    }

    release(target->m_data);
    release(target);

    return succ;
  }
};

}  // namespace dsa

#endif
