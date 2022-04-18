#pragma once

#include <algorithm>

typedef int Rank;

#define DEFAULT_CAPACITY 3

namespace dsa {
    template<typename T>
    class Vector {
    protected:
        Rank m_size;
        Rank m_capacity;
        T   *m_elem;

        void copyFrom(T const *A, Rank lo, Rank hi);
        void expand();
        void shrink();

    public:
        Vector(Rank c = DEFAULT_CAPACITY, Rank s = 0, T v = 0) {
            m_size = 0;
            m_capacity = c;
            m_elem = new T[m_capacity];

            while (m_size < s) {
                m_elem[m_size] = v;
                m_size++;
            }
        }

        Vector(T const *A, Rank n) {
            copyFrom(A, 0, n);
        }

        Vector(T const *A, Rank lo, Rank hi) {
            copyFrom(A, lo, hi);
        }

        Vector(const Vector<T> &V) {
            copyFrom(V.m_elem, 0, V.m_size);
        }

        Vector(const Vector<T> &V, Rank lo, Rank hi) {
            copyFrom(V.m_elem, lo, hi);
        }

        ~Vector() {
            delete[] m_elem;
        }

        T       &operator[](Rank r);
        const T &operator[](Rank r) const;
    };

    template<typename T>
    void Vector<T>::copyFrom(const T *A, Rank lo, Rank hi) {
        m_size = 0;
        m_capacity = (hi - lo) << 1;
        m_elem = new T[m_capacity];

        while (lo < hi) {
            m_elem[m_size] = A[lo];

            m_size++;
            lo++;
        }
    }

    template<typename T>
    void Vector<T>::expand() {
        if (m_size < m_capacity) {
            return;
        }

        T *oldElem = m_elem;
        m_capacity = std::max(m_capacity, DEFAULT_CAPACITY) << 1;
        m_elem = new T[m_capacity];

        for (Rank i = 0; i < m_size; ++i) {
            m_elem[i] = oldElem[i];
        }

        delete[] oldElem;
    }

    template<typename T>
    void Vector<T>::shrink() {
        if ((m_capacity < DEFAULT_CAPACITY << 1) || (m_capacity < m_size << 2)) {
            return;
        }
        T *oldElem = m_elem;
        m_capacity >>= 1;
        m_elem = new T[m_capacity];

        for (int i = 0; i < m_size; ++i) {
            m_elem[i] = oldElem[i];
        }

        delete[] oldElem;
    }

    template<typename T>
    T &Vector<T>::operator[](Rank r) {
        return m_elem[r];
    }

    template<typename T>
    const T &Vector<T>::operator[](Rank r) const {
        return m_elem[r];
    }

}  // namespace dsa
