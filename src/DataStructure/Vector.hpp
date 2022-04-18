#pragma once

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
}  // namespace dsa
