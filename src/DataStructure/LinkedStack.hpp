#pragma once

#include <AutoHeader.hpp>
#include <IStack.hpp>
#include <List.hpp>

namespace dsa {
    template<typename T>
    class LinkedStack : public IStack<T> {
    private:
        List<T> list;

    public:
        LinkedStack() = default;
        ~LinkedStack() = default;

        void push(T const &e) override {
            list.insertAsLast(e);
        }

        T pop() override {
            return list.remove(list.last());
        }

        T &top() override {
            return list[list.size() - 1];
        }

        bool isEmpty() const override {
            return list.size() == 0;
        }
    };
}
