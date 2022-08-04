#ifndef INC_912_DSA_DS_LIST_H_
#define INC_912_DSA_DS_LIST_H_

#include <ds/autoheader.h>
#include <ds/list_node.h>

namespace dsa {
template <class T>
class List {
  using Node = ListNode<T>*;

 protected:
  size_type m_size;
  Node m_header;
  Node m_trailer;

 protected:
  void Init() {
    m_header = new ListNode<T>;
    m_trailer = new ListNode<T>;
    m_size = 0;

    m_header->m_succ = m_trailer;
    m_header->m_pred = nullptr;

    m_trailer->m_pred = m_header;
    m_trailer->m_succ = nullptr;
  }

  size_type Clear() {
    size_type oldSize = m_size;
    while (m_size > 0) {
      Remove(m_header->m_succ);
    }
    return oldSize;
  }

  void CopyNodes(Node p, size_type n) {
    Init();
    while (n > 0) {
      InsertAsLast(p->m_data);
      p = p->m_succ;
      n--;
    }
  }

 public:
  List() { Init(); }

  List(List<T> const& l) { CopyNodes(l.First(), l.m_size); }

  List(List<T> const& l, size_type r, size_type n) { CopyNodes(l[r], n); }

  List(Node p, size_type n) { CopyNodes(p, n); }

  ~List() {
    Clear();
    delete m_header;
    delete m_trailer;
  }

  size_type Size() const { return m_size; }

  Node First() const { return m_header->m_succ; }

  Node Last() const { return m_trailer->m_pred; }

  T& operator[](size_type r) const {
    Node p = First();
    while (r > 0) {
      p = p->m_succ;
      r--;
    }
    return p->m_data;
  }

  Node InsertBefore(Node p, T const& e) {
    m_size++;
    return p->InsertAsPred(e);
  }

  Node InsertAfter(Node p, T const& e) {
    m_size++;
    return p->InsertAsSucc(e);
  }

  Node InsertAsFirst(T const& e) {
    m_size++;
    return m_header->InsertAsSucc(e);
  }

  Node InsertAsLast(T const& e) {
    m_size++;
    return m_trailer->InsertAsPred(e);
  }

  T Remove(Node p) {
    T e = p->m_data;

    p->m_pred->m_succ = p->m_succ;
    p->m_succ->m_pred = p->m_pred;
    delete p;

    m_size--;
    return e;
  }

  Node Find(T const& e, size_type n, Node p) const {
    while (n > 0) {
      p = p->m_pred;
      if (e == p->m_data) {
        return p;
      }
      n--;
    }
    return nullptr;
  }

  size_type Deduplicate() {
    size_type oldSize = m_size;
    Node p = First();
    for (size_type r = 0; p != m_trailer; p = p->m_succ) {
      auto q = Find(p->m_data, r, p);
      if (q != nullptr) {
        Remove(q);
      } else {
        r++;
      }
    }
    return oldSize - m_size;
  }

  template <typename VST>
  void Traverse(VST& visit) {
    Node p = First();
    while (p != m_trailer) {
      visit(p->m_data);
      p = p->m_succ;
    }
  }

  size_type Uniquify() {
    size_type oldSize = m_size;
    Node p = First();
    Node q = p->m_succ;

    while (p != m_trailer) {
      if (p->m_data != q->m_data) {
        p = q;
      } else {
        Remove(q);
      }
      q = p->m_succ;
    }
    return oldSize - m_size;
  }

  Node Search(T const& e, size_type n, Node p) {
    while (n > 0) {
      p = p->m_pred;
      if (e < p->m_data) {
        break;
      }
      n--;
    }
    return p;
  }

  void SelectionSort(Node p, size_type n) {
    // Initialize head and tail
    Node head = p->m_pred;
    Node tail = p;
    for (size_type i = 0; i < n; ++i) {
      tail = tail->m_succ;
    }

    // Compare, select the max item and swap
    while (n > 0) {
      Node max = SelectMax(head->m_succ, n);
      std::swap(max->m_data, tail->m_data);
      tail = tail->m_pred;
      n--;
    }
  }

  Node SelectMax(Node p, size_type n) {
    Node max = p;
    Node cur = p;
    while (n > 1) {
      cur = cur->m_succ;
      if (cur->m_data >= max->m_data) {
        cur = max;
      }
      n--;
    }
    return max;
  }

  void InsertionSort(Node p, size_type n) {
    Node cur = p->m_succ;
    for (size_type i = 1; i < n; ++i) {
      auto pos = Search(cur->m_data, i, cur);
      InsertAfter(pos, cur->m_data);

      cur = cur->m_succ;
      Remove(cur->m_pred);
    }
  }

  void MergeSort(Node p, size_type n) {
    if (n < 2) {
      return;
    }

    Node q = p;
    size_type mi = n >> 1;
    for (size_type i = 0; i < mi; ++i) {
      q = q->m_succ;
    }

    MergeSort(p, mi);
    MergeSort(q, n - mi);

    Merge(this, p, mi, this, q, n - mi);
  }

  void Sort(Node p, size_type n) {
    switch (random() % 3) {
      case 1:
        SelectionSort(p, n);
        break;
      case 2:
        InsertionSort(p, n);
        break;
      default:
        MergeSort(p, n);
        break;
    }
  }
};
}  // namespace dsa

#endif
