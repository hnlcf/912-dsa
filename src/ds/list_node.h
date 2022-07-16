#ifndef INC_912_DSA_DS_LIST_NODE_H_
#define INC_912_DSA_DS_LIST_NODE_H_

#include "autoheader.h"

namespace dsa {
template <typename T>
struct ListNode {
  T m_data{};
  ListNode<T>* m_pred;
  ListNode<T>* m_succ;

  ListNode() = default;

  explicit ListNode(T d) : m_data(d), m_pred(nullptr), m_succ(nullptr) {}

  ListNode(T d, ListNode<T>* p, ListNode<T>* s)
      : m_data(d), m_pred(p), m_succ(s) {}

  ListNode<T>* insertAsPred(T const& e) {
    auto* p = new ListNode(e, m_pred, this);
    m_pred->m_succ = p;
    m_pred = p;
    return p;
  }

  ListNode<T>* insertAsSucc(T const& e) {
    auto* p = new ListNode(e, this, m_succ);
    m_succ->m_pred = p;
    m_succ = p;
    return p;
  }
};
}  // namespace dsa

#endif
