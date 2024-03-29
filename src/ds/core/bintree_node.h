#ifndef INC_912_DSA_DS_BINTREE_NODE_H_
#define INC_912_DSA_DS_BINTREE_NODE_H_

#include <ds/core/queue.h>
#include <ds/core/stack.h>
#include <ds/utils/autoheader.h>

namespace dsa {
template <class T>
struct BinTreeNode;

////////////////////////////////////////////////////////////////////////////
///////////////////// Declaration of static functions //////////////////////
////////////////////////////////////////////////////////////////////////////

/// @brief Determine a node is a leaf node or not
template <class T>
static inline bool isLeaf(BinTreeNode<T>* x) {
  return x->m_left == nullptr && x->m_right == nullptr;
}

/// @brief Determine a node is a root node or not
template <class T>
static inline bool isRoot(BinTreeNode<T>* x) {
  return x->m_parent == nullptr;
}

/// @brief Determine a node has getParent or not
template <class T>
static inline bool hasParent(BinTreeNode<T>* x) {
  return !isRoot(x);
}

/// @brief Determine a node is a left child node or not
template <class T>
static inline bool isLeftChild(BinTreeNode<T>* x) {
  return (!isRoot(x)) && (x == x->m_parent->m_left);
}

/// @brief Determine a node is a right child node or not
template <class T>
static inline bool isRightChild(BinTreeNode<T>* x) {
  return (!isRoot(x)) && (x == x->m_parent->m_right);
}
/// @brief Assist function of preorder traverse
template <class T, class VST>
static void visitAlongLeftBranch(BinTreeNode<T>* x, VST& visit,
                                 Stack<BinTreeNode<T>*>& stack) {
  while (x != nullptr) {
    visit(x->m_data);

    stack.push(x->m_right);
    x = x->m_left;
  }
}
/// @brief Assist function of inorder traverse
template <class T>
static void goAlongLeftBranch(BinTreeNode<T>*         x,
                              Stack<BinTreeNode<T>*>& stack) {
  while (x != nullptr) {
    stack.push(x);
    x = x->m_left;
  }
}

/// @brief Assist function of postorder traverse
template <class T>
static void gotoLeftMostLeaf(Stack<BinTreeNode<T>*>& stack) {
  BinTreeNode<T>* x = stack.top();

  while (x != nullptr) {
    if (x->m_left != nullptr) {
      if (x->m_right != nullptr) {
        stack.push(x->m_right);
      }

      stack.push(x->m_left);
    } else {
      stack.push(x->m_right);
    }

    x = stack.top();
  }

  stack.pop();
}

////////////////////////////////////////////////////////////////////////////
////////////////////// Declaration of Binary-Tree-Node /////////////////////
////////////////////////////////////////////////////////////////////////////

/// @brief Binary Tree Node
template <class T>
struct BinTreeNode {
  T         m_data{};    // data field stored in node
  size_type m_height{};  // height of subtree that rooted in this node

  BinTreeNode<T>* m_parent;
  BinTreeNode<T>* m_left;
  BinTreeNode<T>* m_right;

  BinTreeNode()
      : m_height(0l), m_parent(nullptr), m_left(nullptr), m_right(nullptr) {}

  BinTreeNode(T const& data)
      : BinTreeNode(data, 0ul, nullptr, nullptr, nullptr) {}

  BinTreeNode(T const& data, BinTreeNode<T>* parent)
      : BinTreeNode(data, 0ul, parent, nullptr, nullptr) {}

  BinTreeNode(T const& data, size_type height, BinTreeNode<T>* parent,
              BinTreeNode<T>* left, BinTreeNode<T>* right)
      : m_data(data),
        m_height(height),
        m_parent(parent),
        m_left(left),
        m_right(right) {}

  ~BinTreeNode() = default;

  /// @brief
  BinTreeNode<T>* insertAsLeftChild(T const& e) {
    if (m_left == nullptr) {
      m_left = new BinTreeNode(e, this);
    } else {
      m_left->m_data = e;
    }
    return m_left;
  }

  /// @brief
  BinTreeNode<T>* insertAsRightChild(T const& e) {
    if (m_right == nullptr) {
      m_right = new BinTreeNode(e, this);
    } else {
      m_right->m_data = e;
    }

    return m_right;
  }

  /// @brief Return direct successor of current node(inorder)
  BinTreeNode<T>* successor() {
    auto* succ = this;
    if (m_right != nullptr) {
      succ = m_right;
      while (succ->m_left != nullptr) {
        succ = succ->m_left;
      }
    } else {
      while (isRightChild(succ)) {
        succ = succ->m_parent;
      }
      succ = succ->m_parent;
    }
    return succ;
  }

  /// @brief The total size of the subtree rooted at this node
  size_type size() const {
    size_type s = 1;
    if (m_left != nullptr) {
      s += m_left->size();
    }
    if (m_right != nullptr) {
      s += m_right->size();
    }
    return s;
  }

  /// @brief traverse layer by layer
  template <class VST>
  void traverseLevel(BinTreeNode<T>* x, VST& visit) {
    Queue<BinTreeNode<T>*> queue;
    queue.enqueue(this);

    while (!queue.isEmpty()) {
      x = queue.dequeue();
      visit(x->m_data);

      if (x->m_left != nullptr) {
        queue.enqueue(x->m_left);
      }
      if (x->m_right != nullptr) {
        queue.enqueue(x->m_right);
      }
    }
  }

  /// @brief Preorder traverse of recursive version
  template <class VST>
  void traversePreorderRecur(BinTreeNode<T>* x, VST& visit) {
    if (x == nullptr) {
      return;
    }

    visit(x->m_data);

    traversePreorderRecur(x->m_left, visit);
    traversePreorderRecur(x->m_right, visit);
  }

  /// @brief Preorder traverse of iterative version 1
  template <class VST>
  void traversePreorderIter1(BinTreeNode<T>* x, VST& visit) {
    Stack<BinTreeNode<T>*> s;
    if (x != nullptr) {
      s.push(x);
    }

    while (!s.isEmpty()) {
      x = s.pop();
      visit(x->m_data);

      if (x->m_right != nullptr) {
        s.push(x->m_right);
      }
      if (x->m_left != nullptr) {
        s.push(x->m_left);
      }
    }
  }

  /// @brief Preorder traverse of iterative version 2
  template <class VST>
  void traversePreorderIter2(BinTreeNode<T>* x, VST& visit) {
    Stack<BinTreeNode<T>*> stack;

    while (true) {
      // access the left child chain of x, and push all right child trees to the
      // stack one by one
      visitAlongLeftBranch(x, visit, stack);

      if (stack.isEmpty()) {
        break;
      }
      x = stack.pop();
    }
  }

  /// @brief Inorder traverse of recursive version
  template <class VST>
  void traverseInorderRecur(BinTreeNode<T>* x, VST& visit) {
    if (x == nullptr) {
      return;
    }

    traverseInorderRecur(x->m_left, visit);
    visit(x->m_data);
    traverseInorderRecur(x->m_right, visit);
  }

  /// @brief Inorder traverse of iterative version
  template <class VST>
  void traverseInorderIter(BinTreeNode<T>* x, VST& visit) {
    Stack<BinTreeNode<T>*> stack;

    while (true) {
      goAlongLeftBranch(x, stack);

      if (stack.isEmpty()) {
        break;
      }
      x = stack.pop();

      visit(x->m_data);
      x = x->m_right;
    }
  }

  /// @brief Postorder traverse recursive version
  template <class VST>
  void traversePostorderRecur(BinTreeNode<T>* x, VST& visit) {
    if (x == nullptr) {
      return;
    }

    traversePostorderRecur(x->m_left, visit);
    traversePostorderRecur(x->m_right, visit);
    visit(x->m_data);
  }

  /// @brief Postorder traverse iterative version
  template <class VST>
  void traversePostorderIter(BinTreeNode<T>* x, VST& visit) {
    Stack<BinTreeNode<T>*> stack;
    if (x != nullptr) {
      stack.push(x);
    }

    while (!stack.isEmpty()) {
      if (stack.top() != x->m_parent) {
        // the `stack.top()` must be the right sibling of x
        gotoLeftMostLeaf(stack);
      }

      x = stack.pop();
      visit(x->m_data);
    }
  }

  /// @brief
  bool operator<(BinTreeNode const& other) { return m_data < other.m_data; }

  /// @brief
  bool operator==(BinTreeNode const& other) { return m_data == other.m_data; }
};
}  // namespace dsa

#endif
