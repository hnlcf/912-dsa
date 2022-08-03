#ifndef INC_912_DSA_DS_BTREE_H_
#define INC_912_DSA_DS_BTREE_H_

#include "autoheader.h"
#include "vector.h"

namespace dsa {
template <class T>
struct BTreeNode {
  using Node = BTreeNode<T>*;

 public:
  Node m_parent;
  Vector<T> m_keys;
  Vector<Node> m_childs;

 public:
  BTreeNode() {
    m_parent = nullptr;
    m_childs.Insert(0, nullptr);
  }

  explicit BTreeNode(T const& e) : BTreeNode(e, nullptr, nullptr) {}

  BTreeNode(T const& e, Node l_child, Node r_child) {
    m_parent = nullptr;
    m_keys.Insert(0, e);
    m_childs.Insert(0, l_child);
    m_childs.Insert(1, r_child);

    if (l_child != nullptr) {
      l_child->m_parent = this;
    }
    if (r_child != nullptr) {
      r_child->m_parent = this;
    }
  }
};

template <class T>
class BTree {
  using Node = BTreeNode<T>*;

  static const size_type DEFAULT_ORDER = 3;
  static const size_type DEFAULT_SIZE = 0;

 protected:
  const size_type m_order;  // the rank of btree, At least 3, cannot be modified
  size_type m_size;         // the number of keys in storage
  Node m_root = nullptr;    // the root node
  Node m_hot = nullptr;     // the parent node of current visit

  void SolveOverflow(Node p);

  void SolveUnderflow(Node p);

 public:
  BTree() : BTree(DEFAULT_ORDER, DEFAULT_SIZE) {}

  BTree(size_type order, size_type size) : m_order(order), m_size(size) {
    m_root = new BTreeNode<T>();
  }

  ~BTree() {
    if (m_root != nullptr) {
      Release(m_root);
    }
  }

 public:
  /// @brief Return the order of BTree.
  size_type Order() const { return m_order; }

  /// @brief Return size of BTree.
  size_type Size() const { return m_size; }

  /// @brief
  Node& Root() const { return m_root; }

  /// @brief
  bool IsEmpty() const { return m_size == 0; }

  /// @brief
  Node Search(T const& e) {
    Node target = m_root;
    m_hot = nullptr;

    while (target != nullptr) {
      auto r = target->m_keys.Find(e);

      if ((r >= 0) && (e == target->m_keys[r])) {
        return target;
      }

      m_hot = target;
      target = target->m_childs[r + 1];
    }

    return nullptr;
  }

  /// @brief
  bool Insert(T const& e) { return false; }

  /// @brief
  bool Remove(T const& e) { return false; }
};
}  // namespace dsa

#endif
