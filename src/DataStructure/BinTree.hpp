#pragma once

#include "BinTreeNode.hpp"
#include <algorithm>

template<class T>
using Node = struct dsa::BinTreeNode<T> *;

namespace dsa {
    template<class T>
    static inline size_type stature(Node<T> p);

    template<class T>
    class BinTree {
    public:
    protected:
        size_type m_size;
        Node<T>   m_root;

        virtual size_type updateHeight(Node<T> x);
        void              updateHeightAbove(Node<T> x);

    public:
        BinTree() : BinTree(1ul, new BinTreeNode<T>()) {
        }
        BinTree(size_type size, Node<T> root) : m_size(size), m_root(root) {
        }

    public:
        size_type size() const {
            return m_size;
        }

        bool isEmpty() const {
            return m_root == nullptr;
        }

        Node<T> root() const {
            return m_root;
        }

        Node<T> parent();
        Node<T> firstChild();
        Node<T> nextSibling();

        Node<T> insert(Node<T> x, T const &data);
        Node<T> remove(Node<T> x);
    };

    template<class T>
    size_type BinTree<T>::updateHeight(Node<T> x) {
        x->m_height = 1 + std::max(stature(x->m_left), stature(x->m_right));
        return x->m_height;
    }

    template<class T>
    void BinTree<T>::updateHeightAbove(Node<T> x) {
        while ((x != nullptr)) {
            updateHeight(x);
            x = x->m_parent;
        }
    }

    template<class T>
    Node<T> BinTree<T>::insert(Node<T> x, T const &e) {
        m_size++;
        x->insertAsRightChild(e);
        updateHeightAbove(x);
        return x->m_right;
    }

    template<class T>
    static inline size_type stature(Node<T> p) {
        if (p == nullptr) {
            return -1;
        }
        return p->m_height;
    }
}
