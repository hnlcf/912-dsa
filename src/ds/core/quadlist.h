#ifndef INC_912_DSA_DS_QUADLIST_H_
#define INC_912_DSA_DS_QUADLIST_H_

#include <ds/core/entry.h>
#include <ds/utils/autoheader.h>

namespace dsa {
/// The quadlist node diagram:
///          above
///            ^
///            |
/// prev <-- entry --> next
///            |
///            v
///          below

/// @brief Quad list node, the diagram is as above
template <class T>
struct QuadlistNode {
  T                m_entry;
  QuadlistNode<T>* m_prev;
  QuadlistNode<T>* m_succ;
  QuadlistNode<T>* m_above;
  QuadlistNode<T>* m_below;

  QuadlistNode() : QuadlistNode(T(), nullptr, nullptr, nullptr, nullptr) {}

  explicit QuadlistNode(T entry)
      : QuadlistNode(entry, nullptr, nullptr, nullptr, nullptr) {}

  QuadlistNode(T entry, QuadlistNode<T>* prev, QuadlistNode<T>* succ,
               QuadlistNode<T>* above, QuadlistNode<T>* below)
      : m_entry(entry),
        m_prev(prev),
        m_succ(succ),
        m_above(above),
        m_below(below) {}
};

/// Quadlist, the implementation of skip list

template <class T>
class Quadlist {
  using QlistNode = QuadlistNode<T>*;

 protected:
  /// Initialize list when create
  void init() {
    m_header  = new QuadlistNode<T>();
    m_trailer = new QuadlistNode<T>();

    m_header->m_succ  = m_trailer;
    m_header->m_prev  = nullptr;
    m_header->m_above = nullptr;
    m_header->m_below = nullptr;

    m_trailer->m_prev  = m_header;
    m_trailer->m_succ  = nullptr;
    m_trailer->m_above = nullptr;
    m_trailer->m_below = nullptr;
  }

  /// Clear all nodes
  size_type clear();

 public:
  Quadlist() { init(); }

  ~Quadlist() {
    clear();
    delete m_header;
    delete m_trailer;
  }

  size_type size() const { return m_size; }

  bool isEmpty() const { return size() <= 0; }

  bool isValid(QlistNode p) const {
    return (p != nullptr) && (p != m_header) && (p != m_trailer);
  }

  QlistNode first() const { return m_header->m_succ; }

  QlistNode last() const { return m_trailer->m_prev; }

 private:
  size_type m_size;
  QlistNode m_header;
  QlistNode m_trailer;
};
}  // namespace dsa

#endif
