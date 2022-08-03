/// BST -- Binary Search Tree
#ifndef INC_912_DSA_DS_BST_H_
#define INC_912_DSA_DS_BST_H_

#include "autoheader.h"
#include "bintree.h"

namespace dsa {
template <class T>
class BST : public BinTree<T> {
  using Node = BinTreeNode<T>*;

 protected:
  Node m_hot;  // the GetParent(father) node of the currently visited node

  /// @brief Connect three tree nodes and four subtrees as "3 + 4"
  /// structures(in-Order).
  Node Connect34(Node v1, Node v2, Node v3, Node t1, Node t2, Node t3,
                 Node t4) {
    v1->m_left = t1;
    if (t1 != nullptr) {
      t1->m_parent = v1;
    }
    v1->m_right = t2;
    if (t2 != nullptr) {
      t2->m_parent = v1;
    }
    this->UpdateHeight(v1);

    v3->m_left = t3;
    if (t3 != nullptr) {
      t3->m_parent = v3;
    }
    v3->m_right = t4;
    if (t4 != nullptr) {
      t4->m_parent = v3;
    }
    this->UpdateHeight(v3);

    v2->m_left = v1;
    v1->m_parent = v2;

    v2->m_right = v3;
    v3->m_parent = v2;
    this->UpdateHeight(v2);

    return v2;
  }

  /// @brief Rotate unbalanced locality, `zig` and `zag`
  Node RotateAt(Node v) {
    Node p = v->m_parent;
    Node g = p->m_parent;

    if (IsLeftChild(p)) {
      if (IsLeftChild(v)) {
        // zig-zig
        p->m_parent = g->m_parent;

        return Connect34(v, p, g, v->m_left, v->m_right, p->m_right,
                         g->m_right);
      } else {
        // zig-zag
        v->m_parent = g->m_parent;

        return Connect34(p, v, g, p->m_left, v->m_left, v->m_right, g->m_right);
      }
    } else {
      if (IsRightChild(v)) {
        // zag-zag
        p->m_parent = g->m_parent;

        return Connect34(g, p, v, g->m_left, p->m_left, v->m_left, v->m_right);
      } else {
        // zag-zig
        v->m_parent = g->m_parent;

        return Connect34(g, v, p, g->m_left, v->m_left, v->m_right, p->m_right);
      }
    }
  }

 public:
  /// @brief Find the key `e` in BST.
  virtual Node& Search(T const& e) {
    m_hot = nullptr;
    return SearchInIter(this->m_root, e, m_hot);
  }

  /// @brief Insert the key `e` in BST.
  virtual Node Insert(T const& e) {
    auto& target = Search(e);
    if (target != nullptr) {
      return target;
    }

    target = new BinTreeNode<T>(e, m_hot);

    this->m_size++;
    this->UpdateHeightAbove(target);

    return target;
  }

  /// @brief Delete the key `e` from BST.
  virtual bool Remove(T const& e) {
    auto& target = Search(e);
    if (target == nullptr) {
      return false;
    }

    RemoveAt(target, m_hot);

    this->m_size--;
    this->UpdateHeightAbove(m_hot);

    return true;
  }

 public:
  /// @brief [Recursive version] Find the key `e` in BST subtree rooted At node
  /// `v`.
  /// @param v The reference of root node of subtree.
  /// @param e The key need to be find.
  /// @param hot The GetParent(father) node of the currently visited node.
  static Node& SearchInRecur(Node& v, T const& e, Node& hot) {
    if ((v == nullptr) || (e == v->m_data)) {
      return v;
    }
    hot = v;

    if (e < v->m_data) {
      return SearchInRecur(v->m_left, e, hot);
    } else {
      return SearchInRecur(v->m_right, e, hot);
    }
  }

  /// @brief [Iterative version] Find the key `e` in BST subtree rooted At node
  /// `v`.
  /// @param v The reference of root node of subtree.
  /// @param e The key need to be find.
  /// @param hot The GetParent(father) node of the currently visited node.
  static Node& SearchInIter(Node& v, T const& e, Node& hot) {
    if ((v == nullptr) || (e == v->m_data)) {
      return v;
    }
    hot = v;

    while (true) {
      auto& p = (e < hot->m_data) ? hot->m_left : hot->m_right;

      if ((p == nullptr) || (e == p->m_data)) {
        return p;
      }
      hot = p;
    }
  }

  /// @brief Remove node `p`. (Use for AVL, Splay, RedBlack...)
  /// @param p The reference of tree node to be deleted, must not nullptr.
  /// @param hot The reference of GetParent(father) node of `p`, may be nullptr.
  /// @return A tree node pointer which is the Successor of `p`, may be nullptr.
  static Node RemoveAt(Node& p, Node& hot) {
    Node target = p;
    Node succ;

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

      // find the successor node, because node `p` and its Successor node are
      // adjacent in inorder.
      target = target->Successor();

      // swap datas stored in `p` ans its Successor.
      std::swap(p->m_data, target->m_data);

      // As current `target` is the direct Successor of `p`,
      // so `target` must have not left child.
      succ = target->m_right;

      //! Create connection from GetParent to child.
      // After exchange, determine whether node `p` and its Successor are
      // adjacent or not.
      if (target->m_parent == p) {
        // If adjacent, the `succ` is the right child of `p`.
        target->m_parent->m_right = succ;
      } else {
        // If not, the `succ` is the right child of `target` and `target` is the
        // left child of its GetParent, so `succ` should connect to the left
        // child of GetParent of `target`.
        target->m_parent->m_left = succ;
      }
    }

    //! Create connection from child to GetParent.
    hot = target->m_parent;
    if (succ != nullptr) {
      succ->m_parent = hot;
    }

    Release(target->m_data);
    Release(target);

    return succ;
  }
};

}  // namespace dsa

#endif
