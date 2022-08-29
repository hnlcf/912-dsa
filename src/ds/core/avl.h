#ifndef INC_912_DSA_DS_AVL_H_
#define INC_912_DSA_DS_AVL_H_

#include <ds/core/bst.h>
#include <ds/utils/autoheader.h>

namespace dsa {
template <class T>
class AVL : public BST<T> {
  using Node = BinTreeNode<T>*;

 private:
  enum class BalanceMode : int8_t {
    LeftHeavy     = 1,
    IdealBalanced = 0,
    RightHeavy    = -1,

    Unbalanced = INT8_MIN,
  };

 public:
  /// @brief
  Node insert(T const& e) override {
    Node& target = this->search(e);

    // If already exists, directly return.
    if (target != nullptr) {
      return target;
    }

    // Otherwise create a new node and update size.
    target = new BinTreeNode<T>(e, this->m_hot);
    this->m_size++;

    // Create a copy of new node for return in the end.
    Node copy = target;

    // Determine whether AVL tree is balanced or not. If not, rotate to
    // rebalance. Otherwise, just update tree height.
    for (Node par = this->m_hot; par != nullptr; par = par->m_parent) {
      if (isBalance(par) == BalanceMode::Unbalanced) {
        Node* k = &(this->m_root);

        if (isLeftChild(par)) {
          k = &(par->m_parent->m_left);
        } else if (isRightChild(par)) {
          k = &(par->m_parent->m_right);
        }

        Node unbalance_branch_node = tallerChild(tallerChild(par));
        Node new_grand             = this->rotateAt(unbalance_branch_node);
        *k                         = new_grand;

        break;
      } else {
        this->updateHeight(par);
      }
    }

    return copy;
  }

  /// @brief
  bool remove(T const& e) override {
    Node& target = this->search(e);
    if (target == nullptr) {
      return false;
    }

    this->removeAt(target, this->m_hot);
    this->m_size--;

    // traverse all levels of ancestors from bottom to top.
    for (auto* par = this->m_hot; par != nullptr; par = par->m_parent) {
      if (isBalance(par) == BalanceMode::Unbalanced) {
        Node* k = &(this->m_root);

        if (isLeftChild(par)) {
          k = &(par->m_parent->m_left);
        } else if (isRightChild(par)) {
          k = &(par->m_parent->m_right);
        }

        Node unbalance_branch_node = tallerChild(tallerChild(par));
        Node new_grand             = this->rotateAt(unbalance_branch_node);

        *k  = new_grand;
        par = new_grand;
      }

      this->updateHeight(par);
    }

    return true;
  }

 public:
  /// @brief calculate the balance factor of AVL tree node
  static size_type balanceFactor(Node p) {
    return BinTree<T>::stature(p->m_left) - BinTree<T>::stature(p->m_right);
  }

  /// @brief Determine whether node satisfy the AVL balance
  static BalanceMode isBalance(Node p) {
    switch (balanceFactor(p)) {
      case -1:
        return BalanceMode::RightHeavy;
      case 0:
        return BalanceMode::IdealBalanced;
      case 1:
        return BalanceMode::LeftHeavy;
      default:
        return BalanceMode::Unbalanced;
    }
  }

  /// @brief Return a taller child of `p`
  static Node tallerChild(Node p) {
    auto h = balanceFactor(p);

    if (h > 0) {
      // left child is taller
      return p->m_left;
    } else if (h < 0) {
      // right child is taller
      return p->m_right;
    } else {
      // if equals, return the one that same side with getParent
      if (isLeftChild(p)) {
        return p->m_left;
      } else {
        return p->m_right;
      }
    }
  }
};
}  // namespace dsa

#endif
