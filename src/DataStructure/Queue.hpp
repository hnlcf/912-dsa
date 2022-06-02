#pragma once

#ifndef INCLUDE_912_DSA_QUEUE_HPP
#define INCLUDE_912_DSA_QUEUE_HPP

#include "List.hpp"

using size_type = std::size_t;

namespace dsa {
    template<typename T>
    class Queue {
    private:
        List<T> m_elem;

    public:
        void enqueue(const T &e) {
            m_elem.insertAsLast(e);
        }

        T dequeue() {
            auto tmp = m_elem.first();
            return m_elem.remove(tmp);
        }

        T first() {
            if (size() > 0) {
                return m_elem[0];
            }
            return *(new T);  // return a random value
        }

        T last() {
            if (size() > 0) {
                return m_elem[size() - 1];
            }
            return *(new T);
        }

        size_type size() const {
            return m_elem.size();
        }

        bool isEmpty() const {
            return m_elem.size() == 0;
        }
    };
}

#endif  // INCLUDE_912_DSA_QUEUE_HPP
