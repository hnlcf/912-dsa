#pragma once

#include <iterator>

namespace dsa {
    template<class T>
    class Iterator : public std::iterator<std::input_iterator_tag, T> {
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T *;
        using reference = T &;
        using iterator_category = std::output_iterator_tag;

    public:
        Iterator() : m_ptr(nullptr) {
        }

        explicit Iterator(pointer p) : m_ptr(p) {
        }

        Iterator(const Iterator &other) : m_ptr(other.base()) {
        }

        pointer operator->() const {
            return m_ptr;
        }

        reference operator*() {
            return *m_ptr;
        }

        Iterator &operator++() {
            ++m_ptr;
            return *this;
        }

        Iterator operator++(int) {
            return Iterator(m_ptr++);
        }

        Iterator &operator--() {
            --m_ptr;
            return *this;
        }

        Iterator operator--(int) {
            return Iterator(m_ptr--);
        }

        reference operator[](difference_type n) const {
            return m_ptr[n];
        }

        Iterator &operator+=(difference_type n) {
            m_ptr += n;
            return *this;
        }

        Iterator operator+(difference_type n) {
            return Iterator(m_ptr + n);
        }

        Iterator &operator-=(difference_type n) {
            m_ptr -= n;
            return *this;
        }

        Iterator operator-(difference_type n) {
            return Iterator(m_ptr - n);
        }

        const pointer &base() const {
            return m_ptr;
        }

        Iterator &operator=(const Iterator &iter) {
            if (this == &iter) {
                return *this;
            }
            m_ptr = iter.m_ptr;
            return *this;
        }

        bool operator!=(const Iterator &iter) {
            return m_ptr != iter.m_ptr;
        }

        bool operator==(const Iterator &iter) {
            return m_ptr == iter.m_ptr;
        }

        bool operator<(const Iterator &iter) const {
            return m_ptr < iter.m_ptr;
        }

        bool operator>(const Iterator &iter) const {
            return m_ptr > iter.m_ptr;
        }

        bool operator<=(const Iterator &iter) const {
            return *this < iter || *this == iter;
        }

        bool operator>=(const Iterator &iter) const {
            return *this > iter || *this == iter;
        }

    private:
        pointer m_ptr;
    };
}
