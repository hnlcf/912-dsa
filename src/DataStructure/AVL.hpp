#pragma once

#include <BST.hpp>

namespace dsa {
  template<class T>
  class AVL : public BST<T> {
    using Node = BinTreeNode<T> *;

public:

    Node insert(T const &e) override {
      return nullptr;
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
