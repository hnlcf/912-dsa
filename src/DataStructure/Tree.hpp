#pragma once

template<class T>
struct TreeNode {
    T                   m_value;
    struct TreeNode<T> *m_left;
    struct TreeNode<T> *m_right;

    TreeNode() : TreeNode(0, nullptr, nullptr) {
    }
    TreeNode(T v, struct TreeNode<T> *l, struct TreeNode<T> *r)
      : m_value(v), m_left(l), m_right(r) {
    }
};
