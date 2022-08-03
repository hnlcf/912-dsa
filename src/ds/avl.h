#ifndef INC_912_DSA_DS_AVL_H_
#define INC_912_DSA_DS_AVL_H_

#include "autoheader.h"
#include "bst.h"

namespace dsa {
template <class T>
class AVL : public BST<T> {
  using Node = BinTreeNode<T>*;

 private:
  enum class AVLBalanceMode : int8_t {
    LeftHeavy = 1,
    IdealBalanced = 0,
    RightHeavy = -1,

    Unbalanced = INT8_MIN,
  };

 public:
  /// @brief
  Node Insert(T const& e) override {
    Node& target = this->Search(e);

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
      if (AVLBalance(par) == AVLBalanceMode::Unbalanced) {
        Node* k = &(this->m_root);

        if (IsLeftChild(par)) {
          k = &(par->m_parent->m_left);
        } else if (IsRightChild(par)) {
          k = &(par->m_parent->m_right);
        }

        Node unbalance_branch_node = TallerChild(TallerChild(par));
        Node new_grand = this->RotateAt(unbalance_branch_node);
        *k = new_grand;

        break;
      } else {
        this->UpdateHeight(par);
      }
    }

    return copy;
  }

  /// @brief
  bool Remove(T const& e) override {
    Node& target = this->Search(e);
    if (target == nullptr) {
      return false;
    }

    this->RemoveAt(target, this->m_hot);
    this->m_size--;

    // Traverse all levels of ancestors from bottom to Top.
    for (auto* par = this->m_hot; par != nullptr; par = par->m_parent) {
      if (AVLBalance(par) == AVLBalanceMode::Unbalanced) {
        Node* k = &(this->m_root);

        if (IsLeftChild(par)) {
          k = &(par->m_parent->m_left);
        } else if (IsRightChild(par)) {
          k = &(par->m_parent->m_right);
        }

        Node unbalance_branch_node = TallerChild(TallerChild(par));
        Node new_grand = this->RotateAt(unbalance_branch_node);

        *k = new_grand;
        par = new_grand;
      }

      this->UpdateHeight(par);
    }

    return true;
  }

 public:
  /// @brief Determine whether node satisfy the ideal balance
  static bool IsIdealBalance(Node p) {
    return BinTree<T>::Stature(p->m_left) == BinTree<T>::Stature(p->m_right);
  }

  /// @brief Calculate the balance factor of AVL tree node
  static size_type AVLBalanceFactor(Node p) {
    return BinTree<T>::Stature(p->m_left) - BinTree<T>::Stature(p->m_right);
  }

  /// @brief Determine whether node satisfy the AVL balance
  static AVLBalanceMode AVLBalance(Node p) {
    switch (AVLBalanceFactor(p)) {
      case -1:
        return AVLBalanceMode::RightHeavy;
      case 0:
        return AVLBalanceMode::IdealBalanced;
      case 1:
        return AVLBalanceMode::LeftHeavy;
      default:
        return AVLBalanceMode::Unbalanced;
    }
  }

  /// @brief Return a taller child of `p`
  static Node TallerChild(Node p) {
    auto h = AVLBalanceFactor(p);

    if (h > 0) {
      // left child is taller
      return p->m_left;
    } else if (h < 0) {
      // right child is taller
      return p->m_right;
    } else {
      // if equals, return the one that same side with GetParent
      if (IsLeftChild(p)) {
        return p->m_left;
      } else {
        return p->m_right;
      }
    }
  }
};
}  // namespace dsa

#endif
