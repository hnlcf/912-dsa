#ifndef INC_912_DSA_DS_SPLAYTREE_H_
#define INC_912_DSA_DS_SPLAYTREE_H_

#include <ds/bst.h>

namespace dsa {
template <class T>
class SplayTree : public BST<T> {
  using Node = BinTreeNode<T>*;

 protected:
  /// @brief
  Node splay(Node v) {
    if (v == nullptr) {
      return nullptr;
    }

    Node p, g;
    while ((p = v->m_parent) && (g = p->m_parent)) {
      Node gg = g->m_parent;
      if (isLeftChild(v)) {
        if (isLeftChild(p)) {
          // zig-zig
          attachAsLeftChild(g, p->m_right);
          attachAsLeftChild(p, v->m_right);

          attachAsRightChild(p, g);
          attachAsRightChild(v, p);
        } else {
          // zig-zag
          attachAsRightChild(g, v->m_left);
          attachAsLeftChild(p, v->m_right);

          attachAsLeftChild(v, g);
          attachAsRightChild(v, p);
        }
      } else if (isRightChild(p)) {
        // zag-zag
        attachAsRightChild(g, p->m_left);
        attachAsRightChild(p, v->m_left);

        attachAsLeftChild(p, g);
        attachAsLeftChild(v, p);
      } else {
        // zag-zig
        attachAsLeftChild(g, v->m_right);
        attachAsRightChild(p, v->m_left);

        attachAsRightChild(v, g);
        attachAsLeftChild(v, p);
      }

      if (gg == nullptr) {
        v->m_parent = nullptr;
      } else {
        (g == gg->m_left) ? attachAsLeftChild(gg, v)
                          : attachAsRightChild(gg, v);
      }

      this->updateHeight(g);
      this->updateHeight(p);
      this->updateHeight(v);
    }

    p = v->m_parent;

    // Single splay
    if (p != nullptr) {
      if (isLeftChild(v)) {
        attachAsLeftChild(p, v->m_right);
        attachAsRightChild(v, p);
      } else {
        attachAsRightChild(p, v->m_left);
        attachAsLeftChild(v, p);
      }

      this->updateHeight(p);
      this->updateHeight(v);
    }

    v->m_parent = nullptr;
    return v;
  }

 public:
  /// @brief search an element `e` in splay Tree.
  /// @param e The element to be search
  /// @return Return the ref of pointer point to element if found,
  /// otherwise the ref of node that it should be
  /// inserted.
  Node& search(T const& e) override {
    this->m_hot = nullptr;
    auto p      = this->searchInIter(this->m_root, e, this->m_hot);

    this->m_root = splay((p == nullptr) ? this->m_hot : p);
    return this->m_root;
  }

  Node insert(T const& e) override {
    // If root is null
    if (this->m_root == nullptr) {
      this->m_root = new BinTreeNode<T>(e);
      this->m_size++;

      return this->m_root;
    }

    // If the element exists
    if (e == search(e)->m_data) {
      return this->m_root;
    }

    // Insert the element as new node
    Node t = this->m_root;
    if (e > this->m_root->m_data) {
      this->m_root = new BinTreeNode<T>(e, 0, nullptr, t, t->m_right);
      t->m_parent  = this->m_root;

      if (t->m_right != nullptr) {
        t->m_right->m_parent = this->m_root;
        t->m_right           = nullptr;
      }
    } else {
      this->m_root = new BinTreeNode<T>(e, 0, nullptr, t->m_left, t);
      t->m_parent  = this->m_root;

      if (t->m_left != nullptr) {
        t->m_left->m_parent = this->m_root;
        t->m_left           = nullptr;
      }
    }

    // Update tree size and height of node in per level
    this->m_size++;
    this->updateHeightAbove(t);

    return this->m_root;
  }

  bool remove(T const& e) override {
    if (e != search(e)->m_data) {
      return false;
    }
    return true;
  }

 private:
  /// @brief
  static void attachAsLeftChild(Node v, Node l_child) {
    v->m_left = l_child;
    if (l_child != nullptr) {
      l_child->m_parent = v;
    }
  }

  /// @brief
  static void attachAsRightChild(Node v, Node r_child) {
    v->m_right = r_child;
    if (r_child != nullptr) {
      r_child->m_parent = v;
    }
  }
};
}  // namespace dsa

#endif
