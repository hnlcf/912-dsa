#pragma once

// Core headers
#include <ds/avl.h>
#include <ds/bintree.h>
#include <ds/bintree_node.h>
#include <ds/bst.h>
#include <ds/entry.h>
#include <ds/fib.h>
#include <ds/graph.h>
#include <ds/graph_matrix.h>
#include <ds/iterator.h>
#include <ds/linkedstack.h>
#include <ds/list.h>
#include <ds/list_node.h>
#include <ds/queue.h>
#include <ds/splaytree.h>
#include <ds/stack.h>
#include <ds/vector.h>

// Submodule headers
#include <bitmap/bitmap.h>
#include <bitmap/bitmap_quickinit.h>
#include <stack/stackexample.h>

// Unit test headers
#include <catch2/catch_session.hpp>
#include <catch2/catch_test_macros.hpp>

/// @brief Assist struct for traverse.
template <class T>
struct GetTraverse {
  dsa::Vector<T> m_data{};

  void clear() { m_data.clear(); }

  virtual void operator()(T& e) { m_data.push_back(e); }

  std::string toString() const {
    std::ostringstream os;
    os << m_data;
    return os.str();
  }
};
