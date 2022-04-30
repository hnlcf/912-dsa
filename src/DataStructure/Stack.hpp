#pragma once

#include "Vector.hpp"

namespace dsa {
    template<typename T>
    class Stack : public Vector<T> {

    public:
        void push(T const &e);
        T    pop();
        T   &top();
    };

    template<typename T>
    void Stack<T>::push(const T &e) {
        this->insert(this->size(), e);
    }

    template<typename T>
    T Stack<T>::pop() {
        return this->remove(this->size() - 1);
    }

    template<typename T>
    T &Stack<T>::top() {
        return (*this)[this->size() - 1];
    }
}
