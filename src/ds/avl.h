#ifndef INC_912_DSA_DS_AVL_H_
#define INC_912_DSA_DS_AVL_H_

#include <autoheader.h>
#include <bst.h>

namespace dsa {
template <class T>
class AVL : public BST<T> {
  using Node = BinTreeNode<T>*;

 private:
  enum class BalanceFactor : int8_t {
    LeftHeavy = 1,
    IdealBalanced = 0,
    RightHeavy = -1,

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
    for (auto* par = target->m_parent; par != nullptr; par = par->m_parent) {
      if (isAVLBalance(par) != BalanceFactor::Unbalanced) {
        this->updateHeight(par);
      } else {
        fromParentTo(par) = this->rotateAt(tallerChild(tallerChild(par)));
        break;
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

    // Traverse all levels of ancestors from bottom to top.
    for (auto* par = target->m_parent; par != nullptr; par = par->m_parent) {
      if (isAVLBalance(par) == BalanceFactor::Unbalanced) {
        fromParentTo(par) = this->rotateAt(tallerChild(tallerChild(par)));
        par = fromParentTo(par);
      }

      this->updateHeight(par);
    }

    return true;
  }

 public:
  /// @brief Determine whether node satisfy the ideal balance
  static bool isIdealBalance(Node p) {
    return Bintree<T>::stature(p->m_left) == Bintree<T>::stature(p->m_right);
  }

  /// @brief Calculate the balance factor of AVL tree node
  static size_type balanceFactor(Node p) {
    return Bintree<T>::stature(p->m_left) - Bintree<T>::stature(p->m_right);
  }

  /// @brief Determine whether node satisfy the AVL balance
  static BalanceFactor isAVLBalance(Node p) {
    switch (balanceFactor(p)) {
      case -1:
        return BalanceFactor::RightHeavy;
      case 0:
        return BalanceFactor::IdealBalanced;
      case 1:
        return BalanceFactor::LeftHeavy;
      default:
        return BalanceFactor::Unbalanced;
    }
  }

  /// @brief
  static Node tallerChild(Node p) {
    auto h = balanceFactor(p);

    if (p > 0) {
      // left child is taller
      return p->m_left;
    } else if (p < 0) {
      // right child is taller
      return p->m_right;
    } else {
      // if equals, return the one that same side with parent
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