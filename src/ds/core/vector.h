#ifndef INC_912_DSA_DS_VECTOR_H_
#define INC_912_DSA_DS_VECTOR_H_

#include <ds/core/fib.h>
#include <ds/core/iterator.h>
#include <ds/utils/autoheader.h>

#define VECTOR_RANGE_CHECK(n, size)                                            \
  THROW_OUT_OF_RANGE(                                                          \
      "[ERROR]: dsa::Vector::outOfRangeCheck: n (which is %lld) is out of "    \
      "range "                                                                 \
      "[0, %lld)\n\n",                                                         \
      n, size)

namespace dsa {
template <class T>
class Vector {
 private:
  using value_type      = T;
  using pointer         = T*;
  using reference       = value_type&;
  using iterator        = Iterator<value_type>;
  using const_pointer   = const T*;
  using const_reference = const value_type&;
  using const_iterator  = Iterator<const value_type>;

 public:
  template <class U>
  friend std::ostream& operator<<(std::ostream& os, const Vector<U>&);

  template <class U>
  friend std::istream& operator>>(std::istream& is, Vector<U>&);

 public:
  Vector() : Vector(kDefaultCapacity, 0, 0) {}

  Vector(std::initializer_list<T> list)
      : m_capacity(list.size() << 1), m_size(list.size()) {
    m_elem  = new T[m_capacity];
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

  Vector(const_pointer A, size_type n) { copyFrom(A, 0, n); }

  Vector(const_pointer A, size_type lo, size_type hi) { copyFrom(A, lo, hi); }

  Vector(const Vector<T>& V) { copyFrom(V.m_elem, 0, V.m_size); }

  Vector(const Vector<T>& V, size_type lo, size_type hi) {
    copyFrom(V.m_elem, lo, hi);
  }

  ~Vector() { clean(); }

 public:
  bool isEmpty() const { return m_size == 0; }

  size_type size() const { return m_size; }

  size_type capacity() const { return m_capacity; }

  const_iterator begin() const { return const_iterator(m_elem); }

  const_iterator end() const { return const_iterator(m_elem + m_size); }

  const_iterator cbegin() const { return const_iterator(m_elem); }

  const_iterator cend() const { return const_iterator(m_elem + m_size); }

  const_reference front() const { return *(begin()); }

  const_reference back() const { return *(end() - 1); }

  const_reference at(size_type n) const {
    VECTOR_RANGE_CHECK(n, size());
    return (*this)[n];
  }

  const_reference operator[](size_type r) const {
    VECTOR_RANGE_CHECK(r, size());
    return *(m_elem + r);
  }

  size_type find(const_reference e) const { return find(e, 0, m_size); }

  size_type find(const_reference e, size_type lo, size_type hi) const {
    while (lo < hi) {
      hi--;
      if (e == m_elem[hi]) {
        break;
      }
    }
    return hi;
  }

  iterator begin() { return iterator(m_elem); }

  iterator end() { return iterator(m_elem + m_size); }

  reference front() { return *(begin()); }

  reference back() { return *(end() - 1); }

  reference at(size_type n) {
    VECTOR_RANGE_CHECK(n, size());
    return (*this)[n];
  }

  reference operator[](size_type r) {
    VECTOR_RANGE_CHECK(r, size());
    return *(m_elem + r);
  }

  size_type insert(size_type r, const_reference e) {
    VECTOR_RANGE_CHECK(r, size() + 1);
    expand();

    for (auto it = end(); it > begin() + r; --it) {
      *it = *(it - 1);
    }

    m_elem[r] = e;
    m_size++;
    return r;
  }

  value_type remove(size_type r) {
    VECTOR_RANGE_CHECK(r, size());
    value_type e = m_elem[r];
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

  void pushBack(const_reference e) {
    expand();
    if (m_size == 0) {
      m_elem[0] = e;
      m_size++;
    } else {
      insert(m_size, e);
    }
  }

  value_type popBack() {
    if (m_size == 0) {
      exit(1);
    }
    return remove(m_size - 1);
  }

  void clear() { m_size = 0; }

  void clean() {
    delete[] m_elem;
    m_elem = nullptr;
  }
  size_type deduplicate() {
    size_type oldSize = m_size;
    size_type i       = 1;
    while (i < m_size) {
      if (find(m_elem[i], 0, i) != -1) {
        remove(i);
      } else {
        i++;
      }
    }
    return oldSize - m_size;
  }

  size_type disordered() const {
    size_type n = 0;
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

  void sort(size_type lo, size_type hi) const {
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
  void bubbleSort(size_type lo, size_type hi) const {
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

  void selectionSort(size_type lo, size_type hi) const {
    for (size_type i = lo; i < hi; ++i) {
      value_type min   = m_elem[i];
      size_type  min_i = i;
      for (size_type j = i + 1; j < hi; ++j) {
        if (m_elem[j] < min) {
          min   = m_elem[j];
          min_i = j;
        }
      }
      swap(m_elem[i], m_elem[min_i]);
    }
  }

  /// `O(nlgn)`
  void mergeSort(size_type lo, size_type hi) const {
    if (hi - lo < 2) {
      return;
    }
    size_type mi = (lo + hi) >> 1;
    mergeSort(lo, mi);
    mergeSort(mi, hi);
    merge(lo, mi, hi);
  }

  void merge(size_type lo, size_type mi, size_type hi) const {
    size_type l1 = mi - lo;
    size_type l2 = hi - mi;
    auto      B  = new T[l1];
    auto      C  = new T[l2];

    pointer A = m_elem + lo;
    for (int i = 0; i < l1; ++i) {
      B[i] = A[i];
    }

    A = m_elem + mi;
    for (int i = 0; i < l2; ++i) {
      C[i] = A[i];
    }

    A           = m_elem + lo;
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
  void traverse(VST& visit) {
    for (auto it = begin(); it != end(); ++it) {
      visit(*it);
    }
  }

  std::string toString() const {
    std::ostringstream os;
    os << *this;
    return os.str();
  }

 public:
  /** search */
  size_type search(const_reference e) const { return search(e, 0, m_size); }

  size_type search(const_reference e, size_type lo, size_type hi) const {
    return (random() % 2) == 1 ? binarySearchC(m_elem, e, lo, hi)
                               : fibonacciSearch(m_elem, e, lo, hi);
  }

  static size_type binarySearchA(pointer A, const_reference e, size_type lo,
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

  static size_type binarySearchB(pointer A, const_reference e, size_type lo,
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

  static size_type binarySearchC(pointer A, const_reference e, size_type lo,
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

  static size_type fibonacciSearch(pointer A, const_reference e, size_type lo,
                                   size_type hi) {
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

  static size_type interpolation(pointer A, const_reference e, size_type lo,
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

 protected:
  void copyFrom(const_pointer A, size_type lo, size_type hi) {
    m_size     = 0;
    m_capacity = (hi - lo) << 1;
    m_elem     = new T[m_capacity];

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

    pointer oldElem = m_elem;
    m_capacity      = std::max(m_capacity, kDefaultCapacity) << 1;
    m_elem          = new T[m_capacity];

    for (size_type i = 0; i < m_size; ++i) {
      m_elem[i] = oldElem[i];
    }

    delete[] oldElem;
    oldElem = nullptr;
  }

  void shrink() {
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

 protected:
  static constexpr size_type kDefaultCapacity = 3;

  size_type m_capacity{};
  size_type m_size{};
  pointer   m_elem;
};

template <class T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vec) {
  os << "{ ";
  for (size_type i = 0; i < vec.size(); ++i) {
    os << vec[i];
    if (i < vec.size() - 1) {
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
    vec.pushBack(ele);
  }
  return is;
}

template <class T>
inline bool operator==(const Vector<T>& vec1, const Vector<T>& vec2) {
  return vec1.size() == vec2.size() &&
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
