/// BST -- Binary Search Tree
#pragma once

#include <AutoHeader.hpp>
#include <BinTree.hpp>
#include <Entry.hpp>

namespace dsa {
  template<class T>
  class BST : public BinTree<T> {
    using Node = BinTreeNode<T> *;
    using Tree = BinTree<T> *;

private:
    Node m_hot;  // the parent(father) node of the currently visited node

    /// @brief Connect three tree nodes and four subtrees as "3 + 4" structures.
    Node connect34(Node, Node, Node, Node, Node, Node, Node);

public:
    /// @brief Find the key `e` in BST.
    virtual Node &search(T const &e) {
      m_hot = nullptr;
      return searchIn(this->m_root, e, m_hot);
    }

    /// @brief Insert the key `e` in BST.
    virtual Node insert(T const &e) {
      auto &p = search(e);
      if (p != nullptr) {
        return p;
      }

      p = new BinTreeNode<T>(e, m_hot);

      this->m_size++;
      this->updateHeightAbove(p);

      return p;
    }

    /// @brief Delete the key `e` from BST.
    virtual bool remove(T const &e) {
      auto &p = search(e);
      if (p == nullptr) {
        return false;
      }

      removeAt(p, m_hot);

      this->m_size++;
      this->updateHeightAbove(m_hot);

      return true;
    }

public:
    /// @brief Find the key `e` in BST subtree rooted at node `v`.
    /// @param v The reference of root node of subtree.
    /// @param e The key need to be find.
    /// @param hot The parent(father) node of the currently visited node.
    static Node &searchIn(Node &v, T const &e, Node &hot) {
      if ((v == nullptr) || (e == v->m_data)) {
        return v;
      }

      hot = v;

      if (e < v->m_data) {
        return searchIn(v->m_left, e, hot);
      } else {
        return searchIn(v->m_right, e, hot);
      }
    }

    /// @brief Remove node `p`. (Use for AVL, Splay, RedBlack...)
    /// @param p The reference of tree node to be deleted, must not nullptr.
    /// @param hot The reference of parent(father) node of `p`, may be nullptr.
    /// @return A tree node pointer which is the successor of `p`, may be nullptr.
    static Node removeAt(Node &p, Node &hot) {
      Node target = p;
      Node succ = nullptr;

      if (p->m_left == nullptr) {
        // Only right child exists
        p = p->m_right;
        succ = p;
      } else if (p->m_right == nullptr) {
        // Only left child exists
        p = p->m_left;
        succ = p;
      } else {
        // The left child and right child both exist

        // find the successor node, because node `p` and its successor node are adjacent in inorder.
        target = target->successor();

        // swap datas stored in `p` ans its successor.
        std::swap(p->m_data, target->m_data);

        // As current `target` is the direct successor of `p`,
        // so `target` must have not left child.
        succ = target->m_right;

        // After exchange, determine whether node `p` and its successor are adjacent or not.
        if (target->m_parent == p) {
          // If adjacent, the `succ` is the right child of `p`.
          target->m_parent->m_right = succ;
        } else {
          // If not, the `succ` is the right child of `target` and `target` is the left child of its parent,
          // so `succ` should connect to the left child of parent of `target`.
          target->m_parent->m_left = succ;
        }
      }

      hot = target->m_parent;
      if (succ != nullptr) {
        succ->m_parent = hot;
      }

      release(target->m_data);
      release(target);

      return succ;
    }
  };

}
