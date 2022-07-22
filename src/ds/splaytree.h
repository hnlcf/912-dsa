#ifndef INC_912_DSA_DS_SPLAYTREE_H_
#define INC_912_DSA_DS_SPLAYTREE_H_

#include "autoheader.h"
#include "bst.h"

namespace dsa {
template <class T>
class SplayTree : public BST<T> {
  using Node = BinTreeNode<T>*;

 protected:
  Node splay(Node v) {
    // TODO: Splay -- zig-zig, zag-zag, zig-zag, zag-zig, zig, zag
    return nullptr;
  }

 public:
  /// @brief Search an element `e` in Splay Tree.
  /// @param e The element to be search
  /// @return Return the ref of pointer point to element if found,
  /// otherwise the ref of node that it should be
  /// inserted.
  Node& search(T const& e) override {
    auto& target = this->searchInIter(e);
    if (target != nullptr) {
      splay(target);
    }
    return target;
  }

  Node insert(T const& e) override { return nullptr; }

  bool remove(T const& e) override { return false; }
};
}  // namespace dsa

#endif
