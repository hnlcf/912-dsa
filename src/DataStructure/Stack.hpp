#pragma once

#include "IStack.hpp"
#include "Vector.hpp"

namespace dsa {
    template<typename T>
    class Stack : public IStack<T> {
    private:
        Vector<T> *m_vector;

    public:
        Stack() {
            m_vector = new Vector<T>;
        };

        ~Stack() {
            delete m_vector;
            m_vector = nullptr;
        };

        void push(T const &e);
        T    pop();
        T   &top();
        bool isEmpty();
    };

    template<typename T>
    void Stack<T>::push(const T &e) {
        m_vector->insert(m_vector->size() - 1, e);
    }

    template<typename T>
    T Stack<T>::pop() {
        return m_vector->remove(m_vector->size() - 1);
    }

    template<typename T>
    T &Stack<T>::top() {
        return (*m_vector)[m_vector->size() - 1];
    }

    template<typename T>
    bool Stack<T>::isEmpty() {
        return m_vector->size() == 0;
    }
}
