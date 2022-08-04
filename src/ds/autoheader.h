#ifndef INC_912_DSA_DS_AUTOHEADER_H_
#define INC_912_DSA_DS_AUTOHEADER_H_

#include <fmt/core.h>
#include <fmt/format.h>

#include <cassert>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <typeinfo>

#define THROW_OUT_OF_RANGE(msg, index, right_edge)                    \
  ContainerException::OutOfRangeCheck(msg, __FILE__, __LINE__, index, \
                                      right_edge)

namespace dsa {
using size_type = int64_t;

class ContainerException {
 public:
  static void ThrowOutOfRangeFmt(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
  }

  /// Check n is [0, Size) or not.
  static void OutOfRangeCheck(const char* format, const char* file, int line,
                              size_type n, size_type size) {
    if ((n < 0) || (n >= size)) {
      std::string msg = "[ERROR]: %s:%d\n";
      msg += format;
      ContainerException::ThrowOutOfRangeFmt(msg.c_str(), file, line, n, size);
    }
  }
};

template <class T>
struct Cleaner {
  static void Clean(T x) {  // recursive base
    static long long n = 0;
    if (strlen(typeid(T).name()) <
        7) {  // just output primitive type, ignore elaborate type
      printf("\t<%s>[%lld]=", typeid(T).name(), ++n);
      std::cout << x;
      printf(" purged\n");
    }
  }
};

template <class T>
struct Cleaner<T*> {
  static void Clean(T* x) {
    assert(x);
    delete x;
    x = nullptr;
    // if contains pointer, Release recursively
    static long long n = 0;
    printf("\t<%s>[%lld] released\n", typeid(T*).name(), ++n);
  }
};

template <class T>
void Release(T x) {
  Cleaner<T>::Clean(x);
}
}  // namespace dsa
#endif