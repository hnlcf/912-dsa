#ifndef INC_912_DSA_TEST_TEST_HEADER_H_
#define INC_912_DSA_TEST_TEST_HEADER_H_

// Core headers
#include <ds/core/avl.h>
#include <ds/core/bintree.h>
#include <ds/core/bintree_node.h>
#include <ds/core/bst.h>
#include <ds/core/btree.h>
#include <ds/core/entry.h>
#include <ds/core/fib.h>
#include <ds/core/graph.h>
#include <ds/core/graph_matrix.h>
#include <ds/core/iterator.h>
#include <ds/core/linkedstack.h>
#include <ds/core/list.h>
#include <ds/core/list_node.h>
#include <ds/core/queue.h>
#include <ds/core/splaytree.h>
#include <ds/core/stack.h>
#include <ds/core/vector.h>

// Submodule headers
#include <bitmap/bitmap.h>
#include <bitmap/bitmap_quickinit.h>
#include <stack/stackexample.h>

// Unit test headers
#include <catch2/catch_session.hpp>
#include <catch2/catch_test_macros.hpp>

/// @brief Assist class for traverse.
template <class T>
class GetTraverse {
  dsa::Vector<T>* m_data;

 public:
  GetTraverse() { m_data = new dsa::Vector<T>(); }

  dsa::Vector<T>& data() const { return *m_data; }

  void clear() { m_data->clear(); }

  virtual void operator()(T& e) { m_data->pushBack(e); }

  std::string toString() const {
    std::ostringstream os;
    os << *m_data;
    return os.str();
  }
};

#endif