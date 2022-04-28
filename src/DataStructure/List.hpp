#pragma once

#include "ListNode.hpp"

using Rank = int;

template<typename T>
using Node = dsa::ListNode<T> *;

namespace dsa {

    template<class T>
    class List {

    protected:
    private:
        int     m_size;
        Node<T> m_header;
        Node<T> m_trailer;

    protected:
        void init();
        Rank clear();
        void copyNodes(Node<T> p, int n);

    public:
        List();
        List(List<T> const &l);
        List(List<T> const &l, Rank r, int n);
        List(Node<T> p, int n);
        ~List();

        int     size() const;
        Node<T> first() const;
        Node<T> last() const;
        T      &operator[](Rank r) const;

        Node<T> insertBefore(Node<T> p, T const &e);
        Node<T> insertAfter(Node<T> p, T const &e);
        Node<T> insertAsFirst(T const &e);
        Node<T> insertAsLast(T const &e);
        T       remove(Node<T> p);

        Node<T> find(T const &e, int n, Node<T> p) const;
        Rank    deduplicate();

        template<typename VST>
        void traverse(VST &visit);

        int     uniquify();
        Node<T> search(T const &e, int n, Node<T> p);

        void    selectionSort(Node<T> p, int n);
        Node<T> selectMax(Node<T> p, int n);

        void insertionSort(Node<T> p, int n);

        void mergeSort(Node<T> p, int n);
    };

    template<typename T>
    List<T>::List() {
        init();
    }

    template<typename T>
    List<T>::List(const List<T> &l) {
        copyNodes(l.first(), l.m_size);
    }

    template<typename T>
    List<T>::List(const List<T> &l, Rank r, int n) {
        copyNodes(l[r], n);
    }

    template<typename T>
    List<T>::List(Node<T> p, int n) {
        copyNodes(p, n);
    }

    template<typename T>
    List<T>::~List() {
        clear();
        delete m_header;
        delete m_trailer;
    }

    template<typename T>
    void List<T>::init() {
        m_header = new ListNode<T>;
        m_trailer = new ListNode<T>;
        m_size = 0;

        m_header->m_succ = m_trailer;
        m_header->m_pred = nullptr;

        m_trailer->m_pred = m_header;
        m_trailer->m_succ = nullptr;
    }

    template<typename T>
    Rank List<T>::clear() {
        Rank oldSize = m_size;
        while (m_size > 0) {
            remove(m_header->m_succ);
        }
        return oldSize;
    }

    template<typename T>
    void List<T>::copyNodes(Node<T> p, int n) {
        init();
        while (n > 0) {
            insertAsLast(p->m_data);
            p = p->m_succ;
            n--;
        }
    }

    template<typename T>
    inline int List<T>::size() const {
        return m_size;
    }

    template<typename T>
    inline Node<T> List<T>::first() const {
        return m_header->m_succ;
    }

    template<typename T>
    inline Node<T> List<T>::last() const {
        return m_trailer->m_pred;
    }

    template<typename T>
    T &List<T>::operator[](Rank r) const {
        Node<T> p = first();
        while (r > 0) {
            p = p->m_succ;
            r--;
        }
        return p->m_data;
    }

    template<typename T>
    Node<T> List<T>::insertBefore(Node<T> p, const T &e) {
        m_size++;
        return p->insertAsPred(e);
    }

    template<typename T>
    Node<T> List<T>::insertAfter(Node<T> p, const T &e) {
        m_size++;
        return p->insertAsSucc(e);
    }

    template<typename T>
    Node<T> List<T>::insertAsFirst(const T &e) {
        m_size++;
        return m_header->insertAsSucc(e);
    }

    template<typename T>
    Node<T> List<T>::insertAsLast(const T &e) {
        m_size++;
        return m_trailer->insertAsPred(e);
    }

    template<typename T>
    T List<T>::remove(Node<T> p) {
        T e = p->m_data;

        p->m_pred->m_succ = p->m_succ;
        p->m_succ->m_pred = p->m_pred;
        delete p;

        m_size--;
        return e;
    }

    template<typename T>
    Node<T> List<T>::find(const T &e, int n, Node<T> p) const {
        while (n > 0) {
            p = p->m_pred;
            if (e == p->m_data) {
                return p;
            }
            n--;
        }
        return nullptr;
    }

    template<typename T>
    Rank List<T>::deduplicate() {
        Rank    oldSize = m_size;
        Node<T> p = first();
        for (Rank r = 0; p != m_trailer; p = p->m_succ) {
            auto q = find(p->m_data, r, p);
            if (q != nullptr) {
                remove(q);
            } else {
                r++;
            }
        }
        return oldSize = m_size;
    }

    template<class T>
    template<typename VST>
    void List<T>::traverse(VST &visit) {
        Node<T> p = first();
        while (p != m_trailer) {
            visit(p->m_data);
            p = p->m_succ;
        }
    }

    template<typename T>
    int List<T>::uniquify() {
        Rank    oldSize = m_size;
        Node<T> p = first();
        Node<T> q = p->m_succ;

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

    template<typename T>
    Node<T> List<T>::search(const T &e, int n, Node<T> p) {
        while (n > 0) {
            p = p->m_pred;
            if (e < p->m_data) {
                break;
            }
            n--;
        }
        return p;
    }

    template<typename T>
    void List<T>::selectionSort(Node<T> p, int n) {
        // Initialize head and tail
        Node<T> head = p->m_pred;
        Node<T> tail = p;
        for (int i = 0; i < n; ++i) {
            tail = tail->m_succ;
        }

        // Compare, select the max item and swap
        while (n > 0) {
            Node<T> max = selectMax(head->m_succ, n);
            std::swap(max->m_data, tail->m_data);
            tail = tail->m_pred;
            n--;
        }
    }

    template<typename T>
    Node<T> List<T>::selectMax(Node<T> p, int n) {
        Node<T> max = p;
        Node<T> cur = p;
        while (n > 1) {
            cur = cur->m_succ;
            if (cur->m_data >= max->m_data) {
                cur = max;
            }
            n--;
        }
        return max;
    }

    template<typename T>
    void List<T>::insertionSort(Node<T> p, int n) {
        Node<T> cur = p->m_succ;
        for (int i = 1; i < n; ++i) {
            auto pos = search(cur->m_data, i, cur);
            insertAfter(pos, cur->m_data);

            cur = cur->m_succ;
            remove(cur->m_pred);
        }
    }

    template<typename T>
    static void merge(List<T> &l1, Node<T> &p1, int n1, List<T> &l2, Node<T> p2, int n2) {
        Node<T> head = p1->m_pred;
        while (n2 > 0) {
            if ((n1 > 0) && (p1->m_data < p2->m_data)) {
                p1 = p1->m_succ;

                if (p1 == p2) {
                    break;
                }

                n1--;
            } else {
                p2 = p2->m_succ;

                auto e = l2.remove(p2->m_pred);
                l1.insertBefore(p1, e);

                n2--;
            }
        }
        p1 = head->m_succ;
    }

    template<typename T>
    void List<T>::mergeSort(Node<T> p, int n) {
        if (n < 2) {
            return;
        }

        Node<T> q = p;
        int     mi = n >> 1;
        for (int i = 0; i < mi; ++i) {
            q = q->m_succ;
        }

        mergeSort(p, mi);
        mergeSort(q, n - mi);

        merge(this, p, mi, this, q, n - mi);
    }
}
