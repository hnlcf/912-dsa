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

// TODO: Separate log and release

#define THROW_OUT_OF_RANGE(msg, index, right_edge)                             \
  ContainerException::outOfRangeCheck(msg, __FILE__, __LINE__, index,          \
                                      right_edge)

#define LOG_ERROR(format, ...)                                                 \
  dsa::Log::coreLog(stderr, __FILE__, __LINE__, FMT_STRING(format), __VA_ARGS__)

namespace dsa {
using size_type = int64_t;

class Log {
 public:
  static void coreFmt(FILE* output, fmt::string_view format,
                      fmt::format_args args) {
    fmt::vprint(output, format, args);
  }

  template <typename S, typename... Args>
  static void printFmt(const S& format, Args&&... args, FILE* output = stdout) {
    coreFmt(output, format, fmt::make_format_args(args...));
  }

  template <typename S, typename... Args>
  static void coreLog(FILE* output, const char* file, int32_t line,
                      const S& format, Args&&... args) {
    fmt::print(output, "{}:{} ", file, line);
    coreFmt(output, format, fmt::make_format_args(args...));
  }
};

class ContainerException {
 public:
  static void throwOutOfRangeFmt(FILE* output, const char* format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(output, format, args);
    va_end(args);
  }

  /// Check n is [0, size) or not.
  static void outOfRangeCheck(const char* format, const char* file, int line,
                              size_type n, size_type size) {
    if ((n < 0) || (n >= size)) {
      std::string msg = "[ERROR]: %s:%d\n";
      msg += format;
      ContainerException::throwOutOfRangeFmt(stderr, msg.c_str(), file, line, n,
                                             size);
    }
  }
};

template <class T>
struct Cleaner {
  static void clean(T x) {  // recursive base
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
  static void clean(T* x) {
    delete x;
    x = nullptr;
    // if contains pointer, release recursively
    static long long n = 0;
    printf("\t<%s>[%lld] released\n", typeid(T*).name(), ++n);
  }
};

template <class T>
void release(T x) {
  Cleaner<T>::clean(x);
}
}  // namespace dsa
#endif