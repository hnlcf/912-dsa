#pragma once

#include "IStack.hpp"
#include "List.hpp"

namespace dsa {
    template<typename T>
    class LinkedStack : public IStack<T> {
    private:
        List<T> list;

    public:
        LinkedStack() = default;
        ~LinkedStack() = default;

        void push(T const &e) override;
        T    pop() override;
        T   &top() override;
        bool isEmpty() override;
    };

    template<typename T>
    void LinkedStack<T>::push(const T &e) {
        list.insertAsLast(e);
    }

    template<typename T>
    T LinkedStack<T>::pop() {
        return list.remove(list.last());
    }

    template<typename T>
    T &LinkedStack<T>::top() {
        return list[list.size() - 1];
    }

    template<typename T>
    bool LinkedStack<T>::isEmpty() {
        return list.size() == 0;
    }
}