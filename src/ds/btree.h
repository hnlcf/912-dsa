#ifndef INC_912_DSA_DS_BTREE_H_
#define INC_912_DSA_DS_BTREE_H_

#include <ds/autoheader.h>
#include <ds/vector.h>

namespace dsa {
template <class T>
struct BTreeNode {
  using Node = BTreeNode<T>*;

 public:
  Node         m_parent;
  Vector<T>    m_keys;
  Vector<Node> m_childs;

 public:
  BTreeNode() {
    m_parent = nullptr;
    m_childs.insert(0, nullptr);
  }

  explicit BTreeNode(T const& e) : BTreeNode(e, nullptr, nullptr) {}

  BTreeNode(T const& e, Node l_child, Node r_child) {
    m_parent = nullptr;
    m_keys.insert(0, e);
    m_childs.insert(0, l_child);
    m_childs.insert(1, r_child);

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
 private:
  using Node = BTreeNode<T>*;

  static constexpr size_type kDefaultOrder = 3;
  static constexpr size_type kDefaultSize = 0;

 protected:
  const size_type m_order;  // the rank of btree, At least 3, cannot be modified
  size_type m_size;         // the number of keys in storage
  Node m_root = nullptr;    // the root node
  Node m_hot = nullptr;     // the parent node of current visit

  void SolveOverflow(Node p);

  void SolveUnderflow(Node p);

 public:
  BTree() : BTree(kDefaultOrder, kDefaultSize) {}

  BTree(size_type order, size_type size) : m_order(order), m_size(size) {
    m_root = new BTreeNode<T>();
  }

  ~BTree() {
    if (m_root != nullptr) {
      release(m_root);
    }
  }

 public:
  /// @brief Return `order` of b-tree.
  inline constexpr size_type order() const { return m_order; }

  /// @brief Return `size` of b-tree.
  inline constexpr size_type size() const { return m_size; }

  /// @brief Return `root` node of b-tree.
  inline constexpr Node& root() const { return m_root; }

  /// @brief Return true if b-tree is empty.
  inline constexpr bool isEmpty() const { return m_size == 0; }

  /// @brief Search given value `e` in b-tree. Return node if found,
  /// otherwise `nullptr`.
  Node search(T const& e) const {
    Node target = m_root;
    m_hot       = nullptr;

    while (target != nullptr) {
      auto r = target->m_keys.find(e);

      if ((r >= 0) && (e == target->m_keys[r])) {
        return target;
      }

      m_hot  = target;
      target = target->m_childs[r + 1];
    }

    return nullptr;
  }

  /// @brief
  bool Insert(T const& e) { return false; }

 protected:
  static constexpr size_type kDefaultOrder = 3;
  static constexpr size_type kDefaultSize  = 0;

  const size_type m_order;  // the rank of btree, at least 3, cannot be modified
  size_type       m_size;   // the number of keys in storage

  Node m_root = nullptr;  // the root node
  Node m_hot  = nullptr;  // the parent node of current visit
};

}  // namespace dsa

#endif
