#pragma once

// Core headers
#include <AVL.hpp>
#include <BST.hpp>
#include <BinTree.hpp>
#include <BinTreeNode.hpp>
#include <Entry.hpp>
#include <Fib.hpp>
#include <Graph.hpp>
#include <GraphMatrix.hpp>
#include <Iterator.hpp>
#include <LinkedStack.hpp>
#include <List.hpp>
#include <ListNode.hpp>
#include <Queue.hpp>
#include <Stack.hpp>
#include <Vector.hpp>

// Submodule headers
#include <Bitmap/Bitmap.h>
#include <Bitmap/BitmapQuickInit.h>

#include <Example/StackExample.h>

// Unit test headers
#include <catch2/catch_session.hpp>
#include <catch2/catch_test_macros.hpp>

/// @brief Assist struct for traverse.
template<class T>
struct GetTraverse {
  dsa::Vector<T> m_data{};

  void clear() {
    m_data.clear();
  }

  virtual void operator()(T &e) {
    m_data.push_back(e);
  }

  std::string toString() const {
    std::ostringstream os;
    os << m_data;
    return os.str();
  }
};
