#ifndef INC_912_DSA_DS_RBTREE_H_
#define INC_912_DSA_DS_RBTREE_H_

#include <ds/core/bst.h>

namespace dsa {

template <class T>
class RBTree : public BST<T> {
  using Node = BinTreeNode<T>*;

 public:
  Node insert(const T& e) override { return nullptr; }
  bool remove(const T& e) override { return false; }

 protected:
  /// @brief Update black-height of rb-tree
  size_type updateHeight(Node x) override {
    x->m_height = std::max(this->stature(x->m_left), this->stature(x->m_right));

    if (isBlack(x)) {
      x->m_height++;
    }

    return x->m_height;
  }

  /**
   * NOTE: Revision double red/black in O(1) space when execute dynamical
   * operations.
   */

  /// @brief Solve double red
  void solveDoubleRed(Node x) {}

  /// @brief Solve double black
  void solveDoubleBlack(Node x) {}

 public:
  static bool isBlack(Node x) { return true; }
};

}  // namespace dsa

#endif