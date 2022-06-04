#pragma once

#include "AutoHeader.hpp"
#include "Fib.hpp"
#include <algorithm>

namespace dsa {
    /// Deprecated
    template<class T>
    static size_type binarySearchA(T *A, T const &e, size_type lo, size_type hi);

    /// Deprecated
    template<class T>
    static size_type binarySearchB(T *A, T const &e, size_type lo, size_type hi);

    template<class T>
    static size_type binarySearchC(T *A, T const &e, size_type lo, size_type hi);

    template<class T>
    static size_type fibonacciSearch(T *A, T const &e, size_type lo, size_type hi);

    /// Search `e` in `A[lo, hi]`
    template<class T>
    static size_type interpolation(T *A, T const &e, size_type lo, size_type hi);

    static const size_type DEFAULT_CAPACITY = 3;

    template<class T>
    class Vector {
    protected:
        size_type m_size{};
        size_type m_capacity{};
        T        *m_elem;

        void copyFrom(T const *A, size_type lo, size_type hi) {
            m_size = 0;
            m_capacity = (hi - lo) << 1;
            m_elem = new T[m_capacity];

            while (lo < hi) {
                m_elem[m_size] = A[lo];

                m_size++;
                lo++;
            }
        }

        void expand() {
            if (m_size < m_capacity) {
                return;
            }

            T *oldElem = m_elem;
            m_capacity = std::max(m_capacity, DEFAULT_CAPACITY) << 1;
            m_elem = new T[m_capacity];

            for (size_type i = 0; i < m_size; ++i) {
                m_elem[i] = oldElem[i];
            }

            delete[] oldElem;
            oldElem = nullptr;
        }

        void shrink() {
            if ((m_capacity < DEFAULT_CAPACITY << 1) || (m_capacity < m_size << 2)) {
                return;
            }
            T *oldElem = m_elem;
            m_capacity >>= 1;
            m_elem = new T[m_capacity];

            for (size_type i = 0; i < m_size; ++i) {
                m_elem[i] = oldElem[i];
            }

            delete[] oldElem;
            oldElem = nullptr;
        }

    public:
        Vector(std::initializer_list<T> list) {
            m_size = list.size();
            m_capacity = m_size;
            m_elem = new T[m_capacity];
            T *p = m_elem;
            for (const T &e: list) {
                *p = e;
                p++;
            }
        }

        explicit Vector(size_type c = DEFAULT_CAPACITY, size_type s = 0, T v = 0) {
            m_size = 0;
            m_capacity = c;
            m_elem = new T[m_capacity];

            while (m_size < s) {
                m_elem[m_size] = v;
                m_size++;
            }
        }

        Vector(T const *A, size_type n) {
            copyFrom(A, 0, n);
        }

        Vector(T const *A, size_type lo, size_type hi) {
            copyFrom(A, lo, hi);
        }

        Vector(const Vector<T> &V) {
            copyFrom(V.m_elem, 0, V.m_size);
        }

        Vector(const Vector<T> &V, size_type lo, size_type hi) {
            copyFrom(V.m_elem, lo, hi);
        }

        ~Vector() {
            delete[] m_elem;
            m_elem = nullptr;
        }

        void push_back(T const &e) {
            expand();
            if (m_size == 0) {
                m_elem[0] = e;
                m_size++;
            } else {
                insert(m_size, e);
            }
        }

        T pop_back() {
            if (m_size == 0) {
                return *(new T);
            }
            return remove(m_size - 1);
        }

        // Read-Only interface
        bool isEmpty() const {
            return m_size == 0;
        }

        size_type size() const {
            return m_size;
        }

        size_type insert(size_type r, T const &e) {
            expand();
            for (size_type i = m_size; r < i; i--) {
                m_elem[i] = m_elem[i - 1];
            }
            m_elem[r] = e;
            m_size++;
            return r;
        }

        T remove(size_type r) {
            T e = m_elem[r];
            remove(r, r + 1);
            return e;
        }

        size_type remove(size_type lo, size_type hi) {
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

        size_type find(T const &e) const {
            return find(e, 0, m_size);
        }

        size_type find(T const &e, size_type lo, size_type hi) const {
            while (lo < hi) {
                hi--;
                if (e == m_elem[hi]) {
                    break;
                }
            }
            return hi;
        }

        size_type deduplicate() {
            size_type oldSize = m_size;
            size_type i = 1;
            while (i < m_size) {
                if (find(m_elem[i], 0, i) != -1) {
                    remove(i);
                } else {
                    i++;
                }
            }
            return oldSize - m_size;
        }

        // For sorted Vector
        int disordered() const {
            int n = 0;
            for (size_type i = 1; i < m_size; ++i) {
                if (m_elem[i] < m_elem[i - 1]) {
                    n++;
                }
            }
            return n;
        }

        size_type uniquify() {
            size_type i = 0;
            size_type j = 1;
            while (j < m_size) {
                if (m_elem[i] != m_elem[j]) {
                    i++;
                    m_elem[i] = m_elem[j];
                }
                j++;
            }
            return j - i;
        }

        size_type search(T const &e, size_type lo, size_type hi) const {
            return (random() % 2) == 1 ? binarySearchC(m_elem, e, lo, hi)
                                       : fibonacciSearch(m_elem, e, lo, hi);
        }

        void sort(size_type lo, size_type hi) {
            switch (random() % 3) {
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

        /// `O(n^2)`
        void bubbleSort(size_type lo, size_type hi) {
            hi -= 1;
            size_type last = hi;
            while (lo < hi) {
                last = lo;
                for (size_type i = lo; i < hi; i++) {
                    if (m_elem[i] > m_elem[i + 1]) {
                        swap(m_elem[i], m_elem[i + 1]);
                        last = i;
                    }
                }
                hi = last;
            }
        }

        void selectionSort(size_type lo, size_type hi) {
            for (size_type i = lo; i < hi; ++i) {
                T         min = m_elem[i];
                size_type min_i = i;
                for (size_type j = i + 1; j < hi; ++j) {
                    if (m_elem[j] < min) {
                        min = m_elem[j];
                        min_i = j;
                    }
                }
                swap(m_elem[i], m_elem[min_i]);
            }
        }

        /// `O(nlgn)`
        void mergeSort(size_type lo, size_type hi) {
            if (hi - lo < 2) {
                return;
            }
            size_type mi = (lo + hi) >> 1;
            mergeSort(lo, mi);
            mergeSort(mi, hi);
            merge(lo, mi, hi);
        }

        void merge(size_type lo, size_type mi, size_type hi) {
            size_type l1 = mi - lo;
            size_type l2 = hi - mi;
            T        *B = new T[l1];
            T        *C = new T[l2];

            T *A = m_elem + lo;
            for (int i = 0; i < l1; ++i) {
                B[i] = A[i];
            }

            A = m_elem + mi;
            for (int i = 0; i < l2; ++i) {
                C[i] = A[i];
            }

            A = m_elem + lo;
            size_type i = 0;
            size_type j = 0;
            size_type k = 0;
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
            B = nullptr;
            C = nullptr;
        }

        template<class VST>
        void traverse(VST &visit) {
            for (size_type i = 0; i < m_size; i++) {
                visit(m_elem[i]);
            }
        }

        T &operator[](size_type r) {
            return m_elem[r];
        }

        const T &operator[](size_type r) const {
            return m_elem[r];
        }
    };

    template<class T>
    struct Increase {
        virtual void operator()(T &e) {
            e++;
        }
    };

    template<class T>
    static size_type binarySearchA(T *A, T const &e, size_type lo, size_type hi) {
        while (lo < hi) {
            size_type mi = (lo + hi) >> 1;
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

    template<class T>
    static size_type binarySearchB(T *A, T const &e, size_type lo, size_type hi) {
        while (lo + 1 < hi) {
            size_type mi = (lo + hi) >> 1;
            if (e < A[mi]) {
                hi = mi;
            } else if (A[mi] <= e) {
                lo = mi;
            }
        }
        return e < A[lo] ? lo - 1 : lo;
    }

    template<class T>
    static size_type binarySearchC(T *A, T const &e, size_type lo, size_type hi) {
        while (lo < hi) {
            size_type mi = (lo + hi) >> 1;
            if (e < A[mi]) {
                hi = mi;
            } else if (A[mi] <= e) {
                lo = mi + 1;
            }
        }
        return lo - 1;
    }

    template<class T>
    static size_type fibonacciSearch(T *A, T const &e, size_type lo, size_type hi) {
        Fib fib(hi - lo);
        while (lo + 1 < hi) {
            while ((hi - lo) < fib.get()) {
                fib.prev();
            }
            size_type mi = lo + fib.get() - 1;
            if (e < A[mi]) {
                hi = mi;
            } else if (A[mi] <= e) {
                lo = mi;
            }
        }
        return e < A[lo] ? lo - 1 : lo;
    }

    template<class T>
    static size_type interpolation(T *A, T const &e, size_type lo, size_type hi) {
        while (lo < hi) {
            size_type mi = lo + (hi - lo) * (e - A[lo]) / (A[hi] - A[lo]);
            if (e < A[mi]) {
                hi = mi - 1;
            } else if (A[mi] < e) {
                lo = mi + 1;
            }
        }
        return e == A[lo] ? lo : -1;
    }

}  // namespace dsa
