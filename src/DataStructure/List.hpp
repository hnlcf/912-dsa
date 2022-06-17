#pragma once

#include <AutoHeader.hpp>
#include <ListNode.hpp>
#include <algorithm>

namespace dsa {
    template<class T>
    class List {
        using Node = ListNode<T> *;

    protected:
        size_type m_size;
        Node      m_header;
        Node      m_trailer;

    protected:
        void init() {
            m_header = new ListNode<T>;
            m_trailer = new ListNode<T>;
            m_size = 0;

            m_header->m_succ = m_trailer;
            m_header->m_pred = nullptr;

            m_trailer->m_pred = m_header;
            m_trailer->m_succ = nullptr;
        }

        size_type clear() {
            size_type oldSize = m_size;
            while (m_size > 0) {
                remove(m_header->m_succ);
            }
            return oldSize;
        }

        void copyNodes(Node p, size_type n) {
            init();
            while (n > 0) {
                insertAsLast(p->m_data);
                p = p->m_succ;
                n--;
            }
        }

    public:
        List() {
            init();
        }

        List(List<T> const &l) {
            copyNodes(l.first(), l.m_size);
        }

        List(List<T> const &l, size_type r, size_type n) {
            copyNodes(l[r], n);
        }

        List(Node p, size_type n) {
            copyNodes(p, n);
        }

        ~List() {
            clear();
            delete m_header;
            delete m_trailer;
        }

        size_type size() const {
            return m_size;
        }

        Node first() const {
            return m_header->m_succ;
        }

        Node last() const {
            return m_trailer->m_pred;
        }

        T &operator[](size_type r) const {
            Node p = first();
            while (r > 0) {
                p = p->m_succ;
                r--;
            }
            return p->m_data;
        }

        Node insertBefore(Node p, T const &e) {
            m_size++;
            return p->insertAsPred(e);
        }

        Node insertAfter(Node p, T const &e) {
            m_size++;
            return p->insertAsSucc(e);
        }

        Node insertAsFirst(T const &e) {
            m_size++;
            return m_header->insertAsSucc(e);
        }

        Node insertAsLast(T const &e) {
            m_size++;
            return m_trailer->insertAsPred(e);
        }

        T remove(Node p) {
            T e = p->m_data;

            p->m_pred->m_succ = p->m_succ;
            p->m_succ->m_pred = p->m_pred;
            delete p;

            m_size--;
            return e;
        }

        Node find(T const &e, size_type n, Node p) const {
            while (n > 0) {
                p = p->m_pred;
                if (e == p->m_data) {
                    return p;
                }
                n--;
            }
            return nullptr;
        }

        size_type deduplicate() {
            size_type oldSize = m_size;
            Node      p = first();
            for (size_type r = 0; p != m_trailer; p = p->m_succ) {
                auto q = find(p->m_data, r, p);
                if (q != nullptr) {
                    remove(q);
                } else {
                    r++;
                }
            }
            return oldSize - m_size;
        }

        template<typename VST>
        void traverse(VST &visit) {
            Node p = first();
            while (p != m_trailer) {
                visit(p->m_data);
                p = p->m_succ;
            }
        }

        size_type uniquify() {
            size_type oldSize = m_size;
            Node      p = first();
            Node      q = p->m_succ;

            while (p != m_trailer) {
                if (p->m_data != q->m_data) {
                    p = q;
                } else {
                    remove(q);
                }
                q = p->m_succ;
            }
            return oldSize - m_size;
        }

        Node search(T const &e, size_type n, Node p) {
            while (n > 0) {
                p = p->m_pred;
                if (e < p->m_data) {
                    break;
                }
                n--;
            }
            return p;
        }

        void selectionSort(Node p, size_type n) {
            // Initialize head and tail
            Node head = p->m_pred;
            Node tail = p;
            for (size_type i = 0; i < n; ++i) {
                tail = tail->m_succ;
            }

            // Compare, select the max item and swap
            while (n > 0) {
                Node max = selectMax(head->m_succ, n);
                std::swap(max->m_data, tail->m_data);
                tail = tail->m_pred;
                n--;
            }
        }

        Node selectMax(Node p, size_type n) {
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

        void insertionSort(Node p, size_type n) {
            Node cur = p->m_succ;
            for (size_type i = 1; i < n; ++i) {
                auto pos = search(cur->m_data, i, cur);
                insertAfter(pos, cur->m_data);

                cur = cur->m_succ;
                remove(cur->m_pred);
            }
        }

        void mergeSort(Node p, size_type n) {
            if (n < 2) {
                return;
            }

            Node      q = p;
            size_type mi = n >> 1;
            for (size_type i = 0; i < mi; ++i) {
                q = q->m_succ;
            }

            mergeSort(p, mi);
            mergeSort(q, n - mi);

            merge(this, p, mi, this, q, n - mi);
        }

        void sort(Node p, size_type n) {
            switch (random() % 3) {
                case 1:
                    selectionSort(p, n);
                    break;
                case 2:
                    insertionSort(p, n);
                    break;
                default:
                    mergeSort(p, n);
                    break;
            }
        }
    };
}
