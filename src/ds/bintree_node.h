#ifndef INC_912_DSA_DS_BINTREE_NODE_H_
#define INC_912_DSA_DS_BINTREE_NODE_H_

#include <ds/autoheader.h>
#include <ds/queue.h>
#include <ds/stack.h>

namespace dsa {
template <class T>
struct BinTreeNode;

////////////////////////////////////////////////////////////////////////////
///////////////////// Declaration of static functions //////////////////////
////////////////////////////////////////////////////////////////////////////

/// @brief Determine a node is a leaf node or not
template <class T>
static inline bool IsLeaf(BinTreeNode<T>* x);

/// @brief Determine a node is a root node or not
template <class T>
static inline bool IsRoot(BinTreeNode<T>* x);

/// @brief Determine a node has GetParent or not
template <class T>
static inline bool HasParent(BinTreeNode<T>* x);

/// @brief Determine a node is a left child node or not
template <class T>
static inline bool IsLeftChild(BinTreeNode<T>* x);

/// @brief Determine a node is a right child node or not
template <class T>
static inline bool IsRightChild(BinTreeNode<T>* x);

/// @brief Assist function of preorder Traverse
template <class T, class VST>
static void VisitAlongLeftBranch(BinTreeNode<T>* x, VST& visit,
                                 Stack<BinTreeNode<T>*>& stack);

/// @brief Assist function of inorder Traverse
template <class T>
static void GoAlongLeftBranch(BinTreeNode<T>* x, Stack<BinTreeNode<T>*>& stack);

/// @brief Assist function of postorder Traverse
template <class T>
static void GotoLeftMostLeaf(Stack<BinTreeNode<T>*>& stack);

////////////////////////////////////////////////////////////////////////////
////////////////////// Declaration of Binary-Tree-Node /////////////////////
////////////////////////////////////////////////////////////////////////////

/// @brief Binary Tree Node
template <class T>
struct BinTreeNode {
  T m_data{};            // data field stored in node
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
  BinTreeNode<T>* InsertAsLeftChild(T const& e) {
    if (m_left == nullptr) {
      m_left = new BinTreeNode(e, this);
    } else {
      m_left->m_data = e;
    }
    return m_left;
  }

  /// @brief
  BinTreeNode<T>* InsertAsRightChild(T const& e) {
    if (m_right == nullptr) {
      m_right = new BinTreeNode(e, this);
    } else {
      m_right->m_data = e;
    }

    return m_right;
  }

  /// @brief Return direct Successor of current node(inorder)
  BinTreeNode<T>* Successor() {
    auto* succ = this;
    if (m_right != nullptr) {
      succ = m_right;
      while (succ->m_left != nullptr) {
        succ = succ->m_left;
      }
    } else {
      while (IsRightChild(succ)) {
        succ = succ->m_parent;
      }
      succ = succ->m_parent;
    }
    return succ;
  }

  /// @brief The total Size of the subtree rooted At this node
  size_type Size() const {
    size_type s = 1;
    if (m_left != nullptr) {
      s += m_left->Size();
    }
    if (m_right != nullptr) {
      s += m_right->Size();
    }
    return s;
  }

  /// @brief Traverse layer by layer
  template <class VST>
  void TraverseLevel(BinTreeNode<T>* x, VST& visit) {
    Queue<BinTreeNode<T>*> queue;
    queue.Enqueue(this);

    while (!queue.IsEmpty()) {
      x = queue.Dequeue();
      visit(x->m_data);

      if (x->m_left != nullptr) {
        queue.Enqueue(x->m_left);
      }
      if (x->m_right != nullptr) {
        queue.Enqueue(x->m_right);
      }
    }
  }

  /// @brief Preorder Traverse of recursive version
  template <class VST>
  void TraversePreorderRecur(BinTreeNode<T>* x, VST& visit) {
    if (x == nullptr) {
      return;
    }

    visit(x->m_data);

    TraversePreorderRecur(x->m_left, visit);
    TraversePreorderRecur(x->m_right, visit);
  }

  /// @brief Preorder Traverse of iterative version 1
  template <class VST>
  void TraversePreorderIter1(BinTreeNode<T>* x, VST& visit) {
    Stack<BinTreeNode<T>*> s;
    if (x != nullptr) {
      s.Push(x);
    }

    while (!s.IsEmpty()) {
      x = s.Pop();
      visit(x->m_data);

      if (x->m_right != nullptr) {
        s.Push(x->m_right);
      }
      if (x->m_left != nullptr) {
        s.Push(x->m_left);
      }
    }
  }

  /// @brief Preorder Traverse of iterative version 2
  template <class VST>
  void TraversePreorderIter2(BinTreeNode<T>* x, VST& visit) {
    Stack<BinTreeNode<T>*> stack;

    while (true) {
      // access the left child chain of x, and Push all right child trees to the
      // stack one by one
      VisitAlongLeftBranch(x, visit, stack);

      if (stack.IsEmpty()) {
        break;
      }
      x = stack.Pop();
    }
  }

  /// @brief Inorder Traverse of recursive version
  template <class VST>
  void TraverseInorderRecur(BinTreeNode<T>* x, VST& visit) {
    if (x == nullptr) {
      return;
    }

    TraverseInorderRecur(x->m_left, visit);
    visit(x->m_data);
    TraverseInorderRecur(x->m_right, visit);
  }

  /// @brief Inorder Traverse of iterative version
  template <class VST>
  void TraverseInorderIter(BinTreeNode<T>* x, VST& visit) {
    Stack<BinTreeNode<T>*> stack;

    while (true) {
      GoAlongLeftBranch(x, stack);

      if (stack.IsEmpty()) {
        break;
      }
      x = stack.Pop();

      visit(x->m_data);
      x = x->m_right;
    }
  }

  /// @brief Postorder Traverse recursive version
  template <class VST>
  void TraversePostorderRecur(BinTreeNode<T>* x, VST& visit) {
    if (x == nullptr) {
      return;
    }

    TraversePostorderRecur(x->m_left, visit);
    TraversePostorderRecur(x->m_right, visit);
    visit(x->m_data);
  }

  /// @brief Postorder Traverse iterative version
  template <class VST>
  void TraversePostorderIter(BinTreeNode<T>* x, VST& visit) {
    Stack<BinTreeNode<T>*> stack;
    if (x != nullptr) {
      stack.Push(x);
    }

    while (!stack.IsEmpty()) {
      if (stack.Top() != x->m_parent) {
        // the `stack.Top()` must be the right sibling of x
        GotoLeftMostLeaf(stack);
      }

      x = stack.Pop();
      visit(x->m_data);
    }
  }

  /// @brief
  bool operator<(BinTreeNode const& other) { return m_data < other.m_data; }

  /// @brief
  bool operator==(BinTreeNode const& other) { return m_data == other.m_data; }
};

////////////////////////////////////////////////////////////////////////////
//////////////////// Implementation of static functions ////////////////////
////////////////////////////////////////////////////////////////////////////

template <class T>
static inline bool IsLeaf(BinTreeNode<T>* x) {
  return x->m_left == nullptr && x->m_right == nullptr;
}

template <class T>
static inline bool IsRoot(BinTreeNode<T>* x) {
  return x->m_parent == nullptr;
}

template <class T>
static inline bool HasParent(BinTreeNode<T>* x) {
  return !IsRoot(x);
}

template <class T>
static inline bool IsLeftChild(BinTreeNode<T>* x) {
  return (!IsRoot(x)) && (x == x->m_parent->m_left);
}

template <class T>
static inline bool IsRightChild(BinTreeNode<T>* x) {
  return (!IsRoot(x)) && (x == x->m_parent->m_right);
}

template <class T, class VST>
static void VisitAlongLeftBranch(BinTreeNode<T>* x, VST& visit,
                                 Stack<BinTreeNode<T>*>& stack) {
  while (x != nullptr) {
    visit(x->m_data);

    stack.Push(x->m_right);
    x = x->m_left;
  }
}

template <class T>
static void GoAlongLeftBranch(BinTreeNode<T>* x,
                              Stack<BinTreeNode<T>*>& stack) {
  while (x != nullptr) {
    stack.Push(x);
    x = x->m_left;
  }
}

template <class T>
static void GotoLeftMostLeaf(Stack<BinTreeNode<T>*>& stack) {
  BinTreeNode<T>* x = stack.Top();

  while (x != nullptr) {
    if (x->m_left != nullptr) {
      if (x->m_right != nullptr) {
        stack.Push(x->m_right);
      }

      stack.Push(x->m_left);
    } else {
      stack.Push(x->m_right);
    }

    x = stack.Top();
  }

  stack.Pop();
}
}  // namespace dsa

#endif
