#ifndef INC_912_DSA_DS_BINTREE_H_
#define INC_912_DSA_DS_BINTREE_H_

#include "autoheader.h"
#include "bintree_node.h"

namespace dsa {
template <class T>
class BinTree {
  using Node = BinTreeNode<T>*;
  using Tree = BinTree<T>*;

 protected:
  size_type m_size{};
  Node m_root{};

  /// @brief Update the height of node `x`
  virtual size_type UpdateHeight(Node x) {
    x->m_height = 1 + std::max(Stature(x->m_left), Stature(x->m_right));
    return x->m_height;
  }

  /// @brief Update height of node `x` and all its ancestors.
  void UpdateHeightAbove(Node x) {
    size_type old_height = 0;
    size_type new_height = 0;

    while (x != nullptr) {
      old_height = x->m_height;
      new_height = UpdateHeight(x);

      if (new_height == old_height) {
        break;
      }

      x = x->m_parent;
    }
  }

 public:
  BinTree() : m_size(0), m_root(nullptr) {}

  BinTree(const BinTree<T>& other) : BinTree(other.Size(), other.Root()) {}

  ~BinTree() {
    if (m_size > 0) {
      Remove(m_root);
    }
  }

 public:
  /// @brief
  size_type Size() const { return m_size; }

  /// @brief
  bool IsEmpty() const { return m_root == nullptr; }

  /// @brief
  Node Root() const { return m_root; }

  /// @brief Insert `data` as root node to an empty tree
  Node InsertRoot(T const& data) {
    m_size++;
    m_root = new BinTreeNode<T>(data);

    return m_root;
  }

  /// @brief Insert `data` as the left child node of `x`
  Node InsertAsLeftNode(Node x, T const& data) {
    x->InsertAsLeftChild(data);

    UpdateHeightAbove(x);
    m_size++;

    return x->m_left;
  }

  /// @brief Insert `data` as the right child node of `x`
  Node InsertAsRightNode(Node x, T const& data) {
    x->InsertAsRightChild(data);

    UpdateHeightAbove(x);
    m_size++;

    return x->m_right;
  }

  /// @brief Insert `t` as the left subtree of `x`, and Set `t` to null
  Node AttachAsLeftTree(Tree& t, Node x) {
    // update fields
    x->m_left = t->m_root;
    if (x->m_left != nullptr) {
      x->m_left->m_parent = x;
    }

    UpdateHeightAbove(x);
    m_size += t->m_size;

    // free subtree
    t->m_root = nullptr;
    t->m_size = 0;
    Release(t);

    return x;
  }

  /// @brief Insert `t` as the right subtree of `x`, and Set `t` to null
  Node AttachAsRightTree(Tree& t, Node x) {
    // update fields
    x->m_right = t->m_root;
    if (x->m_right != nullptr) {
      x->m_right->m_parent = x;
    }

    UpdateHeightAbove(x);
    m_size += t->m_size;

    // free subtree
    t->m_root = nullptr;
    t->m_size = 0;
    Release(t);

    return x;
  }

  /// @brief Remove a node `x` and its all child nodes from a tree, return the
  /// number of nodes to be deleted
  size_type Remove(Node x) {
    if (IsRoot(x)) {
      m_root = nullptr;
    } else {
      if (IsLeftChild(x)) {
        x->m_parent->m_left = nullptr;
      } else {
        x->m_parent->m_right = nullptr;
      }
    }

    UpdateHeightAbove(x->m_parent);

    auto n = RemoveAt(x);
    m_size -= n;

    return n;
  }

  /// @brief Remove the subtree `x` and return it as a independent tree
  Tree Secede(Node x) {
    // Cut the connection of `x` and its GetParent.
    IsRoot(x) ? m_root
              : (IsLeftChild(x) ? x->m_parent->m_left : x->m_parent->m_right) =
                    nullptr;
    x->m_parent = nullptr;

    // Update tree height and Size.
    UpdateHeightAbove(x->m_parent);
    m_size -= x->Size();

    // Create a subtree rooted in `x` and return it.
    auto* s = new BinTree<T>;
    s->m_root = x;
    s->m_size = x->Size();

    return s;
  }

  /// @brief
  template <class VST>
  void TraverseLevel(VST& visit) {
    if (m_root) {
      m_root->TraverseLevel(visit);
    }
  }

  /// @brief
  template <class VST>
  void TraversePreorder(VST& visit) {
    if (m_root) {
      m_root->TraversePreorderIter2(m_root, visit);
    }
  }

  /// @brief
  template <class VST>
  void TraverseInorder(VST& visit) {
    if (m_root) {
      m_root->TraverseInorderIter(m_root, visit);
    }
  }

  /// @brief
  template <class VST>
  void TraversePostorder(VST& visit) {
    if (m_root) {
      m_root->TraversePostorderIter(m_root, visit);
    }
  }

  /// @brief Return height of `p`
  static inline size_type Stature(Node p) {
    if (p == nullptr) {
      return -1;
    }

    return p->m_height;
  }

  /// @brief Delete node `x` and its all child nodes, and return number of nodes
  /// to be deleted
  static inline size_type RemoveAt(Node x) {
    // recurse base
    if (x == nullptr) {
      return 0;
    }

    size_type n = 1 + RemoveAt(x->m_left) + RemoveAt(x->m_right);

    Release(x->m_data);
    Release(x);

    return n;
  }
};
}  // namespace dsa

#endif
