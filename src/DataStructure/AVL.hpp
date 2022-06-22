#pragma once

#include <BST.hpp>

namespace dsa {
  template<class T>
  class AVL : public BST<T> {
    using Node = BinTreeNode<T> *;

public:
    Node insert(T const &e) override {
      auto &target = this->search(e);

      // If already exists, directly return.
      if (target != nullptr) {
        return target;
      }

      // Otherwise create a new node and update size.
      target = new BinTreeNode<T>(e, this->m_hot);
      this->m_size++;

      // Create a copy of new node for return in the end.
      Node copy = target;

      // Determine whether AVL tree is balanced or not. If not, rotate to rebalance.
      // Otherwise, just update tree height.
      for (auto par = target->m_parent; par != nullptr; par = par->m_parent) {
        if (!isAVLBalance(par)) {
          // TODO: rotate

          break;
        } else {
          this->updateHeight(par);
        }
      }

      return copy;
    }

    bool remove(T const &e) override {
      return false;
    }

public:
    /// @brief Determine whether node satisfy the ideal balance
    static inline bool isIdealBalance(Node p) {
      return BinTree<T>::stature(p->m_left) == BinTree<T>::stature(p->m_right);
    }

    /// @brief Calculate the balance factor of AVL tree node
    static inline size_type balanceFactor(Node p) {
      return BinTree<T>::stature(p->m_left) - BinTree<T>::stature(p->m_right);
    }

    /// @brief Determine whether node satisfy the AVL balance
    static inline bool isAVLBalance(Node p) {
      return (balanceFactor(p) > -2) && (balanceFactor(p) < 2);
    }
  };
}
