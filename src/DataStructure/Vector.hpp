#pragma once

#include <algorithm>

using Rank = int;

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

        // Read-Only interface
        bool isEmpty() const;
        Rank size() const;
        Rank find(T const &e) const;
        Rank find(T const &e, Rank lo, Rank hi) const;

        void insert(Rank r, T const &e);
        T    remove(Rank r);
        int  remove(Rank lo, Rank hi);
        Rank deduplicate();

        template<typename VST>
        void traverse(VST &visit);

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

        for (Rank i = 0; i < m_size; ++i) {
            m_elem[i] = oldElem[i];
        }

        delete[] oldElem;
    }

    template<typename T>
    Rank Vector<T>::size() const {
        return m_size;
    }

    template<typename T>
    bool Vector<T>::isEmpty() const {
        return m_size == 0;
    }

    template<typename T>
    Rank Vector<T>::find(const T &e) const {
        return find(e, 0, m_size);
    }

    template<typename T>
    Rank Vector<T>::find(const T &e, Rank lo, Rank hi) const {
        while (lo < hi) {
            hi--;
            if (e == m_elem[hi]) {
                break;
            }
        }
        return hi;
    }

    template<typename T>
    void Vector<T>::insert(Rank r, const T &e) {
        expand();
        for (Rank i = m_size; r < i; i--) {
            m_elem[i] = m_elem[i - 1];
        }
        m_elem[r] = e;
        m_size++;
    }

    template<typename T>
    T Vector<T>::remove(Rank r) {
        T e = m_elem[r];
        remove(r, r + 1);
        return e;
    }

    template<typename T>
    int Vector<T>::remove(Rank lo, Rank hi) {
        if (lo == hi) {
            return 0;
        }
        while (hi < m_size) {
            m_elem[lo] = m_elem[hi];

            lo++;
            hi++;
        }
        m_size = lo;
        shrink();
        return hi - lo;
    }

    template<typename T>
    Rank Vector<T>::deduplicate() {
        Rank oldSize = m_size;
        Rank i = 1;
        while (i < m_size) {
            if (find(m_elem[i], 0, i) != -1) {
                remove(i);
            } else {
                i++;
            }
        }
        return oldSize - m_size;
    }

    template<typename T>
    template<typename VST>
    void Vector<T>::traverse(VST &visit) {
        for (Rank i = 0; i < m_size; i++) {
            visit(m_elem[i]);
        }
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
