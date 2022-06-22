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
  };
}
