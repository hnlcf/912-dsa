#pragma once

#include <AutoHeader.hpp>
#include <BinTree.hpp>
#include <Entry.hpp>

namespace dsa {
    template<class T>
    class BST : public BinTree<T> {
        using Node = BinTreeNode<T> *;
        using Tree = BinTree<T> *;

    private:
        Node m_hot;

    public:
        BST();
        BST(BST &&) = default;
        BST(const BST &) = default;
        ~BST();

        BST &operator=(BST &&) = default;
        BST &operator=(const BST &) = default;

    public:
        virtual Node &search(T const &e) {
            m_hot = nullptr;
            return searchIn(this->m_root, e, m_hot);
        }

        virtual Node insert(T const &e) {
            auto &p = search(e);
            if (p != nullptr) {
                return p;
            }

            p = new BinTreeNode<T>(e, m_hot);

            this->m_size++;
            this->updateHeightAbove(p);

            return p;
        }

        virtual bool remove(T const &e);

    public:
        static Node &searchIn(Node &v, T const &e, Node &hot) {
            if ((v == nullptr) || (e == v->m_data)) {
                return v;
            }

            hot = v;

            if (e < v->m_data) {
                return searchIn(v->m_left, e, hot);
            } else {
                return searchIn(v->m_height, e, hot);
            }
        }
    };

}
