#ifndef INC_912_DSA_DS_SPLAYTREE_H_
#define INC_912_DSA_DS_SPLAYTREE_H_

#include <ds/bst.h>

namespace dsa {
template <class T>
class SplayTree : public BST<T> {
  using Node = BinTreeNode<T>*;

 protected:
  /// @brief
  Node Splay(Node v) {
    if (v == nullptr) {
      return nullptr;
    }

    Node p, g;
    while ((p = v->m_parent) && (g = p->m_parent)) {
      Node gg = g->m_parent;
      if (IsLeftChild(v)) {
        if (IsLeftChild(p)) {
          // zig-zig
          AttachAsLeftChild(g, p->m_right);
          AttachAsLeftChild(p, v->m_right);

          AttachAsRightChild(p, g);
          AttachAsRightChild(v, p);
        } else {
          // zig-zag
          AttachAsRightChild(g, v->m_left);
          AttachAsLeftChild(p, v->m_right);

          AttachAsLeftChild(v, g);
          AttachAsRightChild(v, p);
        }
      } else if (IsRightChild(p)) {
        // zag-zag
        AttachAsRightChild(g, p->m_left);
        AttachAsRightChild(p, v->m_left);

        AttachAsLeftChild(p, g);
        AttachAsLeftChild(v, p);
      } else {
        // zag-zig
        AttachAsLeftChild(g, v->m_right);
        AttachAsRightChild(p, v->m_left);

        AttachAsRightChild(v, g);
        AttachAsLeftChild(v, p);
      }

      if (gg == nullptr) {
        v->m_parent = nullptr;
      } else {
        (g == gg->m_left) ? AttachAsLeftChild(gg, v)
                          : AttachAsRightChild(gg, v);
      }

      this->UpdateHeight(g);
      this->UpdateHeight(p);
      this->UpdateHeight(v);
    }

    p = v->m_parent;

    // Single Splay
    if (p != nullptr) {
      if (IsLeftChild(v)) {
        AttachAsLeftChild(p, v->m_right);
        AttachAsRightChild(v, p);
      } else {
        AttachAsRightChild(p, v->m_left);
        AttachAsLeftChild(v, p);
      }

      this->UpdateHeight(p);
      this->UpdateHeight(v);
    }

    v->m_parent = nullptr;
    return v;
  }

 public:
  /// @brief Search an element `e` in Splay Tree.
  /// @param e The element to be Search
  /// @return Return the ref of pointer point to element if found,
  /// otherwise the ref of node that it should be
  /// inserted.
  Node& Search(T const& e) override {
    this->m_hot = nullptr;
    auto p = this->SearchInIter(this->m_root, e, this->m_hot);

    this->m_root = Splay((p == nullptr) ? this->m_hot : p);
    return this->m_root;
  }

  Node Insert(T const& e) override {
    // If root is null
    if (this->m_root == nullptr) {
      this->m_root = new BinTreeNode<T>(e);
      this->m_size++;

      return this->m_root;
    }

    // If the element exists
    if (e == Search(e)->m_data) {
      return this->m_root;
    }

    // Insert the element as new node
    Node t = this->m_root;
    if (e > this->m_root->m_data) {
      this->m_root = new BinTreeNode<T>(e, 0, nullptr, t, t->m_right);
      t->m_parent = this->m_root;

      if (t->m_right != nullptr) {
        t->m_right->m_parent = this->m_root;
        t->m_right = nullptr;
      }
    } else {
      this->m_root = new BinTreeNode<T>(e, 0, nullptr, t->m_left, t);
      t->m_parent = this->m_root;

      if (t->m_left != nullptr) {
        t->m_left->m_parent = this->m_root;
        t->m_left = nullptr;
      }
    }

    // Update tree Size and height of node in per level
    this->m_size++;
    this->UpdateHeightAbove(t);

    return this->m_root;
  }

  bool Remove(T const& e) override {
    if (e != Search(e)->m_data) {
      return false;
    }
    return true;
  }

 private:
  /// @brief
  static void AttachAsLeftChild(Node v, Node l_child) {
    v->m_left = l_child;
    if (l_child != nullptr) {
      l_child->m_parent = v;
    }
  }

  /// @brief
  static void AttachAsRightChild(Node v, Node r_child) {
    v->m_right = r_child;
    if (r_child != nullptr) {
      r_child->m_parent = v;
    }
  }
};
}  // namespace dsa

#endif
