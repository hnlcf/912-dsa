#pragma once

#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo>

#define THROW_OUT_OF_RANGE(msg, index, right_edge)                                                 \
  ContainerException::outOfRangeCheck(msg, __FILE__, __LINE__, index, right_edge)

namespace dsa {
  using size_type = int64_t;

  class ContainerException {
public:
    static void throwOutOfRangeFmt(const char *format, ...) {
      va_list args;
      va_start(args, format);
      vfprintf(stderr, format, args);
      va_end(args);
    }

    /// Check n is [0, size) or not.
    static void outOfRangeCheck(const char *format,
                                const char *file,
                                int         line,
                                size_type   n,
                                size_type   size) {
      if ((n < 0) || (n >= size)) {
        std::string msg = "[ERROR]: %s:%d\n";
        msg += format;
        ContainerException::throwOutOfRangeFmt(msg.c_str(), file, line, n, size);
      }
    }
  };

  template<class T>
  struct Cleaner {
    static void clean(T x) {  // 相当于递归基
      static long long n = 0;
      if (strlen(typeid(T).name()) < 7) {  // 复杂类型一概忽略，只输出基本类型
        printf("\t<%s>[%lld]=", typeid(T).name(), ++n);
        std::cout << x;
        printf(" purged\n");
      }
    }
  };

  template<class T>
  struct Cleaner<T *> {
    static void clean(T *x) {
      if (x != nullptr) {
        delete x;
      }
      // if contains pointer, release recursively
      static long long n = 0;
      printf("\t<%s>[%lld] released\n", typeid(T *).name(), ++n);
    }
  };

  template<class T>
  void release(T x) {
    Cleaner<T>::clean(x);
  }
}
