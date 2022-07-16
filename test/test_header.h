#pragma once

// Core headers
#include <avl.h>
#include <bintree.h>
#include <bintree_node.h>
#include <bst.h>
#include <entry.h>
#include <fib.h>
#include <graph.h>
#include <graph_matrix.h>
#include <iterator.h>
#include <linkedstack.h>
#include <list.h>
#include <list_node.h>
#include <queue.h>
#include <stack.h>
#include <vector.h>

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
