#pragma once

#include "AutoHeader.hpp"
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

        void push(T const &e) override {
            m_vector->push_back(e);
        }

        T pop() override {
            return m_vector->pop_back();
        }

        T &top() override {
            return (*m_vector)[m_vector->size() - 1];
        }

        bool isEmpty() const override {
            return m_vector->size() == 0;
        }
    };
}
