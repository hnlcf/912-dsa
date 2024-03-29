#ifndef INC_912_DSA_DS_BINTREE_H_
#define INC_912_DSA_DS_BINTREE_H_

#include <ds/core/bintree_node.h>
#include <ds/utils/autoheader.h>

namespace dsa {
template <class T>
class BinTree {
  using Node = BinTreeNode<T>*;
  using Tree = BinTree<T>*;

 protected:
  size_type m_size{};
  Node      m_root{};

  /// @brief Update the height of node `x`
  virtual size_type updateHeight(Node x) {
    x->m_height = 1 + std::max(stature(x->m_left), stature(x->m_right));
    return x->m_height;
  }

  /// @brief Update height of node `x` and all its ancestors.
  void updateHeightAbove(Node x) {
    size_type old_height = 0;
    size_type new_height = 0;

    while (x != nullptr) {
      old_height = x->m_height;
      new_height = updateHeight(x);

      if (new_height == old_height) {
        break;
      }

      x = x->m_parent;
    }
  }

 public:
  BinTree() : m_size(0), m_root(nullptr) {}

  BinTree(const BinTree<T>& other) : BinTree(other.size(), other.root()) {}

  ~BinTree() {
    if (m_size > 0) {
      remove(m_root);
    }
  }

 public:
  /// @brief
  size_type size() const { return m_size; }

  /// @brief
  bool isEmpty() const { return m_root == nullptr; }

  /// @brief
  Node root() const { return m_root; }

  /// @brief Insert `data` as root node to an empty tree
  Node insertRoot(T const& data) {
    m_size++;
    m_root = new BinTreeNode<T>(data);

    return m_root;
  }

  /// @brief Insert `data` as the left child node of `x`
  Node insertAsLeftNode(Node x, T const& data) {
    x->insertAsLeftChild(data);

    updateHeightAbove(x);
    m_size++;

    return x->m_left;
  }

  /// @brief Insert `data` as the right child node of `x`
  Node insertAsRightNode(Node x, T const& data) {
    x->insertAsRightChild(data);

    updateHeightAbove(x);
    m_size++;

    return x->m_right;
  }

  /// @brief Insert `t` as the left subtree of `x`, and set `t` to null
  Node attachAsLeftTree(Tree& t, Node x) {
    // update fields
    x->m_left = t->m_root;
    if (x->m_left != nullptr) {
      x->m_left->m_parent = x;
    }

    updateHeightAbove(x);
    m_size += t->m_size;

    // free subtree
    t->m_root = nullptr;
    t->m_size = 0;
    release(t);

    return x;
  }

  /// @brief Insert `t` as the right subtree of `x`, and set `t` to null
  Node attachAsRightTree(Tree& t, Node x) {
    // update fields
    x->m_right = t->m_root;
    if (x->m_right != nullptr) {
      x->m_right->m_parent = x;
    }

    updateHeightAbove(x);
    m_size += t->m_size;

    // free subtree
    t->m_root = nullptr;
    t->m_size = 0;
    release(t);

    return x;
  }

  /// @brief Remove a node `x` and its all child nodes from a tree, return the
  /// number of nodes to be deleted
  size_type remove(Node x) {
    if (isRoot(x)) {
      m_root = nullptr;
    } else {
      if (isLeftChild(x)) {
        x->m_parent->m_left = nullptr;
      } else {
        x->m_parent->m_right = nullptr;
      }
    }

    updateHeightAbove(x->m_parent);

    auto n = removeAt(x);
    m_size -= n;

    return n;
  }

  /// @brief Remove the subtree `x` and return it as a independent tree
  Tree secede(Node x) {
    // Cut the connection of `x` and its getParent.
    isRoot(x) ? m_root
              : (isLeftChild(x) ? x->m_parent->m_left : x->m_parent->m_right) =
                    nullptr;
    x->m_parent = nullptr;

    // Update tree height and size.
    updateHeightAbove(x->m_parent);
    m_size -= x->size();

    // Create a subtree rooted in `x` and return it.
    auto* s   = new BinTree<T>;
    s->m_root = x;
    s->m_size = x->size();

    return s;
  }

  /// @brief
  template <class VST>
  void traverseLevel(VST& visit) {
    if (m_root) {
      m_root->traverseLevel(visit);
    }
  }

  /// @brief
  template <class VST>
  void traversePreorder(VST& visit) {
    if (m_root) {
      m_root->traversePreorderIter2(m_root, visit);
    }
  }

  /// @brief
  template <class VST>
  void traverseInorder(VST& visit) {
    if (m_root) {
      m_root->traverseInorderIter(m_root, visit);
    }
  }

  /// @brief
  template <class VST>
  void traversePostorder(VST& visit) {
    if (m_root) {
      m_root->traversePostorderIter(m_root, visit);
    }
  }

  /// @brief Return height of `p`
  static inline size_type stature(Node p) {
    if (p == nullptr) {
      return -1;
    }

    return p->m_height;
  }

  /// @brief Delete node `x` and its all child nodes, and return number of nodes
  /// to be deleted
  static inline size_type removeAt(Node x) {
    // recurse base
    if (x == nullptr) {
      return 0;
    }

    size_type n = 1 + removeAt(x->m_left) + removeAt(x->m_right);

    release(x->m_data);
    release(x);

    return n;
  }
};
}  // namespace dsa

#endif
