#pragma once

#include <algorithm>
#include <cstdlib>

#include "Fib.hpp"

using Rank = int;

#define DEFAULT_CAPACITY 3

namespace dsa {

    /// Deprecated
    template<typename T>
    static Rank binarySearchA(T *A, T const &e, Rank lo, Rank hi);

    /// Deprecated
    template<typename T>
    static Rank binarySearchB(T *A, T const &e, Rank lo, Rank hi);

    template<typename T>
    static Rank binarySearchC(T *A, T const &e, Rank lo, Rank hi);

    template<typename T>
    static Rank fibonacciSearch(T *A, T const &e, Rank lo, Rank hi);

    /// Search `e` in `A[lo, hi]`
    template<typename T>
    static Rank interpolation(T *A, T const &e, Rank lo, Rank hi);

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
        void insert(Rank r, T const &e);
        T    remove(Rank r);
        int  remove(Rank lo, Rank hi);

        Rank find(T const &e) const;
        Rank find(T const &e, Rank lo, Rank hi) const;
        Rank deduplicate();

        // For sorted Vector
        int  disordered() const;
        Rank uniquify();

        Rank search(T const &e, Rank lo, Rank hi) const;

        void sort(Rank lo, Rank hi);

        /// `O(n^2)`
        void bubbleSort(Rank lo, Rank hi);
        void selectionSort(Rank lo, Rank hi);

        /// `O(nlgn)`
        void mergeSort(Rank lo, Rank hi);
        void merge(Rank lo, Rank mi, Rank hi);

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
    int Vector<T>::disordered() const {
        int n = 0;
        for (Rank i = 1; i < m_size; ++i) {
            if (m_elem[i] < m_elem[i - 1]) {
                n++;
            }
        }
        return n;
    }

    template<typename T>
    Rank Vector<T>::uniquify() {
        Rank i = 0;
        Rank j = 1;
        while (j < m_size) {
            if (m_elem[i] != m_elem[j]) {
                i++;
                m_elem[i] = m_elem[j];
            }
            j++;
        }
        return j - i;
    }

    // Search `e` in `A[lo, hi)`
    template<typename T>
    Rank Vector<T>::search(T const &e, Rank lo, Rank hi) const {
        return (rand() % 2) == 1 ? binarySearchC(m_elem, e, lo, hi)
                                 : fibonacciSearch(m_elem, e, lo, hi);
    }

    template<typename T>
    void Vector<T>::sort(Rank lo, Rank hi) {
        switch (rand() % 3) {
            case 1:
                bubbleSort(lo, hi);
                break;
            case 2:
                selectionSort(lo, hi);
                break;
            default:
                mergeSort(lo, hi);
                break;
        }
    }

    template<typename T>
    void Vector<T>::bubbleSort(Rank lo, Rank hi) {
        hi -= 1;
        Rank last = hi;
        while (lo < hi) {
            last = lo;
            for (Rank i = lo; i < hi; i++) {
                if (m_elem[i] > m_elem[i + 1]) {
                    swap(m_elem[i], m_elem[i + 1]);
                    last = i;
                }
            }
            hi = last;
        }
    }

    template<typename T>
    void Vector<T>::selectionSort(Rank lo, Rank hi) {
        for (Rank i = lo; i < hi; ++i) {
            T    min = m_elem[i];
            Rank min_i = i;
            for (Rank j = i + 1; j < hi; ++j) {
                if (m_elem[j] < min) {
                    min = m_elem[j];
                    min_i = j;
                }
            }
            swap(m_elem[i], m_elem[min_i]);
        }
    }

    template<typename T>
    void Vector<T>::mergeSort(Rank lo, Rank hi) {
        if (hi - lo < 2) {
            return;
        }
        Rank mi = (lo + hi) >> 1;
        mergeSort(lo, mi);
        mergeSort(mi, hi);
        merge(lo, mi, hi);
    }

    template<typename T>
    void Vector<T>::merge(Rank lo, Rank mi, Rank hi) {
        Rank l1 = mi - lo;
        Rank l2 = hi - mi;
        T   *B = new T[l1];
        T   *C = new T[l2];

        T *A = m_elem + lo;
        for (int i = 0; i < l1; ++i) {
            B[i] = A[i];
        }

        A = m_elem + mi;
        for (int i = 0; i < l2; ++i) {
            C[i] = A[i];
        }

        A = m_elem + lo;
        Rank i = 0;
        Rank j = 0;
        Rank k = 0;
        while ((j < l1) && (k < l2)) {
            if (B[j] < C[k]) {
                A[i] = B[j];
                j++;
            } else {
                A[i] = C[k];
                k++;
            }
            i++;
        }

        while (j < l1) {
            A[i] = B[j];
            j++;
            i++;
        }

        while (k < l2) {
            A[i] = C[k];
            k++;
            i++;
        }

        delete[] C;
        delete[] B;
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

    template<typename T>
    struct Increase {
        virtual void operator()(T &e) {
            e++;
        }
    };

    template<typename T>
    static Rank binarySearchA(T *A, T const &e, Rank lo, Rank hi) {
        while (lo < hi) {
            Rank mi = (lo + hi) >> 1;
            if (e < A[mi]) {
                hi = mi;
            } else if (A[mi] < e) {
                lo = mi + 1;
            } else {
                return mi;
            }
        }
        return -1;
    }

    template<typename T>
    static Rank binarySearchB(T *A, T const &e, Rank lo, Rank hi) {
        while (lo + 1 < hi) {
            Rank mi = (lo + hi) >> 1;
            if (e < A[mi]) {
                hi = mi;
            } else if (A[mi] <= e) {
                lo = mi;
            }
        }
        return e < A[lo] ? lo - 1 : lo;
    }

    template<typename T>
    static Rank binarySearchC(T *A, T const &e, Rank lo, Rank hi) {
        while (lo < hi) {
            Rank mi = (lo + hi) >> 1;
            if (e < A[mi]) {
                hi = mi;
            } else if (A[mi] <= e) {
                lo = mi + 1;
            }
        }
        return lo - 1;
    }

    template<typename T>
    static Rank fibonacciSearch(T *A, T const &e, Rank lo, Rank hi) {
        Fib fib(hi - lo);
        while (lo + 1 < hi) {
            while ((hi - lo) < fib.get()) {
                fib.prev();
            }
            Rank mi = lo + fib.get() - 1;
            if (e < A[mi]) {
                hi = mi;
            } else if (A[mi] <= e) {
                lo = mi;
            }
        }
        return e < A[lo] ? lo - 1 : lo;
    }

    template<typename T>
    static Rank interpolation(T *A, T const &e, Rank lo, Rank hi) {
        while (lo < hi) {
            Rank mi = lo + (hi - lo) * (e - A[lo]) / (A[hi] - A[lo]);
            if (e < A[mi]) {
                hi = mi - 1;
            } else if (A[mi] < e) {
                lo = mi + 1;
            }
        }
        return e == A[lo] ? lo : -1;
    }

}  // namespace dsa
