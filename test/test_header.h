#ifndef INC_912_DSA_TEST_TEST_HEADER_H_
#define INC_912_DSA_TEST_TEST_HEADER_H_

// Core headers
#include <ds/avl.h>
#include <ds/bintree.h>
#include <ds/bintree_node.h>
#include <ds/bst.h>
#include <ds/btree.h>
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

/// @brief Assist class for Traverse.
template <class T>
class GetTraverse {
  dsa::Vector<T>* m_data;

 public:
  GetTraverse() { m_data = new dsa::Vector<T>(); }

  dsa::Vector<T>& Data() const { return *m_data; }

  void Clear() { m_data->Clear(); }

  virtual void operator()(T& e) { m_data->PushBack(e); }

  std::string ToString() const {
    std::ostringstream os;
    os << *m_data;
    return os.str();
  }
};

#endif