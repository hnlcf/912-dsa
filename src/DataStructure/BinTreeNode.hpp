#pragma once

#include <cstdint>

using size_type = int64_t;

namespace dsa {
    template<class T>
    struct BinTreeNode {
        T         m_data;
        size_type m_height;

        BinTreeNode<T> *m_parent;
        BinTreeNode<T> *m_left;
        BinTreeNode<T> *m_right;

        BinTreeNode() : BinTreeNode(0ul, 0ul, nullptr, nullptr, nullptr) {
        }

        BinTreeNode(T const &data, BinTreeNode<T> *parent)
          : BinTreeNode(data, 0ul, parent, nullptr, nullptr) {
        }

        BinTreeNode(T const        &data,
                    size_type       height,
                    BinTreeNode<T> *parent,
                    BinTreeNode<T> *left,
                    BinTreeNode<T> *right)
          : m_data(data), m_height(height), m_parent(parent), m_left(left), m_right(right) {
        }

        ~BinTreeNode() {
        }

        BinTreeNode<T> *insertAsLeftChild(T const &e);

        BinTreeNode<T> *insertAsRightChild(T const &e);

        /// Return direct successor of current node(inorder)
        BinTreeNode<T> *successor();

        /// The total size of the subtree rooted at this node
        size_type size();

        /// Traverse layer by layer
        template<class VST>
        void traverseLevel(BinTreeNode<T> *x, VST &visit);

        /// Preorder traverse
        template<class VST>
        void traversePreorder(BinTreeNode<T> *x, VST &visit);

        /// Inorder traverse
        template<class VST>
        void traverseInorder(BinTreeNode<T> *x, VST &visit);

        /// Postorder traverse
        template<class VST>
        void traversePostorder(BinTreeNode<T> *x, VST &visit);
    };

    template<class T>
    BinTreeNode<T> *BinTreeNode<T>::insertAsLeftChild(T const &e) {
        m_left = new BinTreeNode(e, this);
        return m_left;
    }

    template<class T>
    BinTreeNode<T> *BinTreeNode<T>::insertAsRightChild(T const &e) {
        m_right = new BinTreeNode(e, this);
        return m_right;
    }

    template<class T>
    size_type BinTreeNode<T>::size() {
        size_type s = 1;
        if (m_left != nullptr) {
            s += m_left->size();
        }
        if (m_right != nullptr) {
            s += m_right->size();
        }
        return s;
    }

    template<class T>
    template<class VST>
    void BinTreeNode<T>::traversePreorder(BinTreeNode<T> *x, VST &visit) {
        if (x == nullptr) {
            return;
        }
        visit(x->m_data);
        traversePreorder(x->m_left, visit);
        traversePreorder(x->m_right, visit);
    }

    template<class T>
    template<class VST>
    void BinTreeNode<T>::traverseInorder(BinTreeNode<T> *x, VST &visit) {
        if (x == nullptr) {
            return;
        }
        traverseInorder(x->m_left, visit);
        visit(x->m_data);
        traverseInorder(x->m_right, visit);
    }

    template<class T>
    template<class VST>
    void BinTreeNode<T>::traversePostorder(BinTreeNode<T> *x, VST &visit) {
        if (x == nullptr) {
            return;
        }
        traversePostorder(x->m_left, visit);
        traversePostorder(x->m_right, visit);
        visit(x->m_data);
    }
}
