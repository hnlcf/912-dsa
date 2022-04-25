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

    public:
        int     size() const;
        Node<T> first() const;
        Node<T> last() const;
        T      &operator[](Rank r) const;

        Node<T> insertBefore(Node<T> p, T const &e);
        Node<T> insertAfter(Node<T> p, T const &e);
        T       remove(Node<T> p);
    };

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
        Node<T> temp = first();
        while (r > 0) {
            temp = temp->m_succ;
            r--;
        }
        return temp->m_data;
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
    T List<T>::remove(Node<T> p) {
        T e = p->m_data;

        p->m_pred->m_succ = p->m_succ;
        p->m_succ->m_pred = p->m_pred;
        delete p;

        m_size--;
        return e;
    }
}