#pragma once

#include "AutoHeader.hpp"
#include "BinTreeNode.hpp"
#include <algorithm>

namespace dsa {
    template<class T>
    class BinTree {
        using Node = BinTreeNode<T> *;
        using Tree = BinTree<T> *;

    protected:
        size_type m_size{};
        Node      m_root{};

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
        BinTree() : BinTree(1l, new BinTreeNode<T>()) {
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

        /// Insert `data` as root node to an empty tree
        Node insertRoot(T const &data) {
            m_size++;
            m_root = new BinTreeNode<T>(data);
            return m_root;
        }

        /// Insert `data` as the left child node of `x`
        Node insertAsLeftNode(Node x, T const &data) {
            m_size++;
            x->insertAsLeftChild(data);
            updateHeightAbove(x);
            return x->m_left;
        }

        /// Insert `data` as the right child node of `x`
        Node insertAsRightNode(Node x, T const &data) {
            m_size++;
            x->insertAsRightChild(data);
            updateHeightAbove(x);
            return x->m_right;
        }

        /// Insert `t` as the left subtree of `x`, and set `t` to null
        Node attachAsLeftTree(Tree &t, Node x) {
            // update fields
            x->m_left = t->m_root;
            if (x->m_left != nullptr) {
                x->m_left->m_parent = x;
            }
            m_size += t->m_size;
            updateHeightAbove(x);

            // free subtree
            t->m_root = nullptr;
            t->m_size = 0;
            release(t);
            t = nullptr;

            return x;
        }

        /// Insert `t` as the right subtree of `x`, and set `t` to null
        Node attachAsRightTree(Tree &t, Node x) {
            // update fields
            x->m_right = t->m_root;
            if (x->m_right != nullptr) {
                x->m_right->m_parent = x;
            }
            m_size += t->m_size;
            updateHeightAbove(x);

            // free subtree
            t->m_root = nullptr;
            t->m_size = 0;
            release(t);
            t = nullptr;

            return x;
        }

        /// Remove a node `x` and its all child nodes from a tree, return the number of nodes to be deleted
        size_type remove(Node x) {
            isRoot(x) ? m_root
                      : (isLeftChild(x) ? x->m_parent->m_left : x->m_parent->m_right) = nullptr;
            updateHeightAbove(x->m_parent);

            auto  n = removeAt(x);
            m_size -= n;
            return n;
        }

        /// Remove the subtree `x` and return it as a independent tree
        Tree secede(Node x) {
            isRoot(x) ? m_root
                      : (isLeftChild(x) ? x->m_parent->m_left : x->m_parent->m_right) = nullptr;
            x->m_parent = nullptr;
            updateHeightAbove(x->m_parent);
            m_size -= x->size();

            autotree = new BinTree<T>;
            tree->m_root = x;
            tree->m_size = x->size();
            return tree;
        }


        template<class VST>
        void traverseLevel(VST &visit) {
            if (m_root) {
                m_root->traverseLevel(visit);
            }
        }

        template<class VST>
        void traversePreorder(VST &visit) {
            if (m_root) {
                m_root->traversePreorderIter2(m_root, visit);
            }
        }

        template<class VST>
        void traverseInorder(VST &visit) {
            if (m_root) {
                m_root->traverseInorderIter(m_root, visit);
            }
        }

        template<class VST>
        void traversePostorder(VST &visit) {
            if (m_root) {
                m_root->traversePostorderIter(m_root, visit);
            }
        }

        /// Return height of `p`
        static inline size_type stature(Node p) {
            if (p == nullptr) {
                return -1;
            }
            return p->m_height;
        }

        /// Delete node `x` and its all child nodes, and return number of nodes to be deleted
        static inline size_type removeAt(Node x) {
            // recurse base
            if (x == nullptr) {
                return 0;
            }
            size_type n = 1 + removeAt(x->m_left) + removeAt(x->m_right);
            release(x->m_data);
            release(x);

            return n;
        }
    };
}
