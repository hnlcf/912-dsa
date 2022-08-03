#ifndef INC_912_DSA_DS_VECTOR_H_
#define INC_912_DSA_DS_VECTOR_H_

#include "autoheader.h"
#include "fib.h"
#include "iterator.h"

#define VECTOR_RANGE_CHECK(n, size)                                         \
  THROW_OUT_OF_RANGE(                                                       \
      "[ERROR]: dsa::Vector::OutOfRangeCheck: n (which is %lld) is out of " \
      "range "                                                              \
      "[0, %lld)\n\n",                                                      \
      n, size)

namespace dsa {
static const size_type kDefaultCapacity = 3;

template <class T>
class Vector {
 private:
  using value_type = T;
  using pointer = T*;
  using reference = value_type&;
  using iterator = Iterator<value_type>;
  using const_pointer = const T*;
  using const_reference = const value_type&;
  using const_iterator = Iterator<const value_type>;

 protected:
  size_type m_capacity{};
  size_type m_size{};
  pointer m_elem;

  void CopyFrom(const_pointer A, size_type lo, size_type hi) {
    m_size = 0;
    m_capacity = (hi - lo) << 1;
    m_elem = new T[m_capacity];

    while (lo < hi) {
      m_elem[m_size] = A[lo];

      m_size++;
      lo++;
    }
  }

  void Expand() {
    if (m_size < m_capacity) {
      return;
    }

    pointer oldElem = m_elem;
    m_capacity = std::max(m_capacity, kDefaultCapacity) << 1;
    m_elem = new T[m_capacity];

    for (size_type i = 0; i < m_size; ++i) {
      m_elem[i] = oldElem[i];
    }

    delete[] oldElem;
    oldElem = nullptr;
  }

  void Shrink() {
    if ((m_capacity < kDefaultCapacity << 1) || (m_capacity < m_size << 2)) {
      return;
    }
    pointer oldElem = m_elem;
    m_capacity >>= 1;
    m_elem = new T[m_capacity];

    for (size_type i = 0; i < m_size; ++i) {
      m_elem[i] = oldElem[i];
    }

    delete[] oldElem;
    oldElem = nullptr;
  }

 public:
  Vector() : Vector(kDefaultCapacity, 0, 0) {}

  Vector(std::initializer_list<T> list)
      : m_capacity(list.size() << 1), m_size(list.size()) {
    m_elem = new T[m_capacity];
    auto it = begin();
    for (const_reference e : list) {
      *it = e;
      ++it;
    }
  }

  Vector(size_type size, T default_value)
      : Vector(size << 1, size, default_value) {}

  Vector(size_type capacity, size_type size, T default_value)
      : m_capacity(capacity), m_size(size) {
    m_elem = new T[m_capacity];

    for (auto it = begin(); it != end(); ++it) {
      *it = default_value;
    }
  }

  Vector(const_pointer A, size_type n) { CopyFrom(A, 0, n); }

  Vector(const_pointer A, size_type lo, size_type hi) { CopyFrom(A, lo, hi); }

  Vector(const Vector<T>& V) { CopyFrom(V.m_elem, 0, V.m_size); }

  Vector(const Vector<T>& V, size_type lo, size_type hi) {
    CopyFrom(V.m_elem, lo, hi);
  }

  ~Vector() {
    delete[] m_elem;
    m_elem = nullptr;
  }

  iterator begin() { return iterator(m_elem); }

  iterator end() { return iterator(m_elem + m_size); }

  const_iterator begin() const { return const_iterator(m_elem); }

  const_iterator end() const { return const_iterator(m_elem + m_size); }

  const_iterator cbegin() const { return const_iterator(m_elem); }

  const_iterator cend() const { return const_iterator(m_elem + m_size); }

  void PushBack(const_reference e) {
    Expand();
    if (m_size == 0) {
      m_elem[0] = e;
      m_size++;
    } else {
      Insert(m_size, e);
    }
  }

  value_type PopBack() {
    if (m_size == 0) {
      return *(new T);
    }
    return Remove(m_size - 1);
  }

  void Clear() { m_size = 0; }

  reference Front() { return *(begin()); }

  const_reference Front() const { return *(begin()); }

  reference Back() { return *(end() - 1); }

  const_reference Back() const { return *(end() - 1); }

  reference At(size_type n) {
    VECTOR_RANGE_CHECK(n, Size());
    return (*this)[n];
  }

  const_reference At(size_type n) const {
    VECTOR_RANGE_CHECK(n, Size());
    return (*this)[n];
  }

  // Read-Only interface
  bool IsEmpty() const { return m_size == 0; }

  size_type Size() const { return m_size; }

  size_type Capacity() const { return m_capacity; }

  size_type Insert(size_type r, const_reference e) {
    VECTOR_RANGE_CHECK(r, Size() + 1);
    Expand();

    for (auto it = end(); it > begin() + r; --it) {
      *it = *(it - 1);
    }

    m_elem[r] = e;
    m_size++;
    return r;
  }

  value_type Remove(size_type r) {
    VECTOR_RANGE_CHECK(r, Size());
    value_type e = m_elem[r];
    Remove(r, r + 1);
    return e;
  }

  size_type Remove(size_type lo, size_type hi) {
    if (lo == hi) {
      return 0;
    }
    while (hi < m_size) {
      m_elem[lo] = m_elem[hi];

      lo++;
      hi++;
    }
    m_size = lo;
    Shrink();
    return hi - lo;
  }

  size_type Find(const_reference e) const { return Find(e, 0, m_size); }

  size_type Find(const_reference e, size_type lo, size_type hi) const {
    while (lo < hi) {
      hi--;
      if (e == m_elem[hi]) {
        break;
      }
    }
    return hi;
  }

  size_type Deduplicate() {
    size_type oldSize = m_size;
    size_type i = 1;
    while (i < m_size) {
      if (Find(m_elem[i], 0, i) != -1) {
        Remove(i);
      } else {
        i++;
      }
    }
    return oldSize - m_size;
  }

  // For sorted Vector
  size_type Disordered() const {
    size_type n = 0;
    for (size_type i = 1; i < m_size; ++i) {
      if (m_elem[i] < m_elem[i - 1]) {
        n++;
      }
    }
    return n;
  }

  size_type Uniquify() {
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

  size_type Search(const_reference e) const { return Search(e, 0, m_size); }

  size_type Search(const_reference e, size_type lo, size_type hi) const {
    return (random() % 2) == 1 ? BinarySearchC(m_elem, e, lo, hi)
                               : FibonacciSearch(m_elem, e, lo, hi);
  }

  void Sort(size_type lo, size_type hi) {
    switch (random() % 3) {
      case 1:
        BubbleSort(lo, hi);
        break;
      case 2:
        SelectionSort(lo, hi);
        break;
      default:
        MergeSort(lo, hi);
        break;
    }
  }

  /// `O(n^2)`
  void BubbleSort(size_type lo, size_type hi) {
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

  void SelectionSort(size_type lo, size_type hi) {
    for (size_type i = lo; i < hi; ++i) {
      value_type min = m_elem[i];
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
  void MergeSort(size_type lo, size_type hi) {
    if (hi - lo < 2) {
      return;
    }
    size_type mi = (lo + hi) >> 1;
    MergeSort(lo, mi);
    MergeSort(mi, hi);
    Merge(lo, mi, hi);
  }

  void Merge(size_type lo, size_type mi, size_type hi) {
    size_type l1 = mi - lo;
    size_type l2 = hi - mi;
    auto B = new T[l1];
    auto C = new T[l2];

    pointer A = m_elem + lo;
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

  template <class VST>
  void Traverse(VST& visit) {
    for (auto it = begin(); it != end(); ++it) {
      visit(*it);
    }
  }

  std::string ToString() const {
    std::ostringstream os;
    os << *this;
    return os.str();
  }

  reference operator[](size_type r) {
    VECTOR_RANGE_CHECK(r, Size());
    return *(m_elem + r);
  }

  const_reference operator[](size_type r) const {
    VECTOR_RANGE_CHECK(r, Size());
    return *(m_elem + r);
  }

  template <class U>
  friend std::ostream& operator<<(std::ostream& os, const Vector<U>&);

  template <class U>
  friend std::istream& operator>>(std::istream& is, Vector<U>&);

  static size_type BinarySearchA(pointer A, const_reference e, size_type lo,
                                 size_type hi) {
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

  static size_type BinarySearchB(pointer A, const_reference e, size_type lo,
                                 size_type hi) {
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

  static size_type BinarySearchC(pointer A, const_reference e, size_type lo,
                                 size_type hi) {
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

  static size_type FibonacciSearch(pointer A, const_reference e, size_type lo,
                                   size_type hi) {
    Fib fib(hi - lo);
    while (lo + 1 < hi) {
      while ((hi - lo) < fib.Get()) {
        fib.Prev();
      }
      size_type mi = lo + fib.Get() - 1;
      if (e < A[mi]) {
        hi = mi;
      } else if (A[mi] <= e) {
        lo = mi;
      }
    }
    return e < A[lo] ? lo - 1 : lo;
  }

  static size_type Interpolation(pointer A, const_reference e, size_type lo,
                                 size_type hi) {
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
};

template <class T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vec) {
  os << "{ ";
  for (size_type i = 0; i < vec.Size(); ++i) {
    os << vec[i];
    if (i < vec.Size() - 1) {
      os << ", ";
    }
  }
  os << " }";

  return os;
}

template <class T>
std::istream& operator>>(std::istream& is, Vector<T>& vec) {
  T ele;
  while (is >> ele) {
    vec.PushBack(ele);
  }
  return is;
}

template <class T>
inline bool operator==(const Vector<T>& vec1, const Vector<T>& vec2) {
  return vec1.Size() == vec2.Size() &&
         std::equal(vec1.begin(), vec1.end(), vec2.begin());
}

template <class T>
inline bool operator!=(const Vector<T>& vec1, const Vector<T>& vec2) {
  return !(vec1 == vec2);
}

template <class T>
struct Increase {
  virtual void operator()(T& e) { e++; }
};
}  // namespace dsa

#endif
