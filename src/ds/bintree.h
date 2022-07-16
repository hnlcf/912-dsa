#ifndef INC_912_DSA_DS_BINTREE_H_
#define INC_912_DSA_DS_BINTREE_H_

#include <autoheader.h>
#include <bintree_node.h>
#include <algorithm>

namespace dsa {
template <class T>
class Bintree {
  using Node = BinTreeNode<T>*;
  using Tree = Bintree<T>*;

 protected:
  size_type m_size{};
  Node m_root{};

  /// @brief
  virtual size_type updateHeight(Node x) {
    x->m_height = 1 + std::max(stature(x->m_left), stature(x->m_right));
    return x->m_height;
  }

  /// @brief
  void updateHeightAbove(Node x) {
    while ((x != nullptr)) {
      updateHeight(x);
      x = x->m_parent;
    }
  }

 public:
  Bintree() : m_size(0), m_root(nullptr) {}

  Bintree(const Bintree<T>& other) : Bintree(other.size(), other.root()) {}

  ~Bintree() {
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

  /// @breif Insert `data` as root node to an empty tree
  Node insertRoot(T const& data) {
    m_size++;
    m_root = new BinTreeNode<T>(data);

    return m_root;
  }

  /// @breif Insert `data` as the left child node of `x`
  Node insertAsLeftNode(Node x, T const& data) {
    x->insertAsLeftChild(data);

    updateHeightAbove(x);
    m_size++;

    return x->m_left;
  }

  /// @breif Insert `data` as the right child node of `x`
  Node insertAsRightNode(Node x, T const& data) {
    x->insertAsRightChild(data);

    updateHeightAbove(x);
    m_size++;

    return x->m_right;
  }

  /// @breif Insert `t` as the left subtree of `x`, and set `t` to null
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
    t = nullptr;

    return x;
  }

  /// @breif Insert `t` as the right subtree of `x`, and set `t` to null
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
    t = nullptr;

    return x;
  }

  /// @breif Remove a node `x` and its all child nodes from a tree, return the
  /// number of nodes to be deleted
  size_type remove(Node x) {
    isRoot(x) ? m_root
              : (isLeftChild(x) ? x->m_parent->m_left : x->m_parent->m_right) =
                    nullptr;
    updateHeightAbove(x->m_parent);

    auto n = removeAt(x);
    m_size -= n;

    return n;
  }

  /// @brief Remove the subtree `x` and return it as a independent tree
  Tree secede(Node x) {
    // Cut the connect of `x` and its parent.
    isRoot(x) ? m_root
              : (isLeftChild(x) ? x->m_parent->m_left : x->m_parent->m_right) =
                    nullptr;
    x->m_parent = nullptr;

    // Update tree height and size.
    updateHeightAbove(x->m_parent);
    m_size -= x->size();

    // Create a subtree rooted in `x` and return it.
    auto* s = new Bintree<T>;
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

  /// @breif Delete node `x` and its all child nodes, and return number of nodes
  /// to be deleted
  static inline size_type removeAt(Node x) {
    // recurse base
    if (x == nullptr) {
      return 0;
    }

    size_type n = 1 + removeAt(x->m_left) + removeAt(x->m_right);

    release(x->m_data);
    release(x);
    x = nullptr;

    return n;
  }
};
}  // namespace dsa

#endif