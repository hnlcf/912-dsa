#pragma once

#include "AutoHeader.hpp"
#include "BinTreeNode.hpp"
#include <algorithm>

namespace dsa {
    template<class T>
    class BinTree {
        using Node = BinTreeNode<T> *;

    protected:
        size_type m_size;
        Node      m_root;

        virtual size_type updateHeight(Node x) {
            x->m_height = 1 + std::max(stature(x->m_left), stature(x->m_right));
            return x->m_height;
        }

        void updateHeightAbove(Node x) {
            while ((x != nullptr)) {
                updateHeight(x);
                x = x->m_parent;
            }
        }

    public:
        BinTree() : BinTree(1ul, new BinTreeNode<T>()) {
        }
        BinTree(size_type size, Node root) : m_size(size), m_root(root) {
        }

    public:
        size_type size() const {
            return m_size;
        }

        bool isEmpty() const {
            return m_root == nullptr;
        }

        Node root() const {
            return m_root;
        }

        Node parent();
        Node firstChild();
        Node nextSibling();

        Node insert(Node x, T const &data) {
            m_size++;
            x->insertAsRightChild(data);
            updateHeightAbove(x);
            return x->m_right;
        }

        Node remove(Node x);

        static size_type stature(Node p) {
            if (p == nullptr) {
                return -1;
            }
            return p->m_height;
        }
    };
}
