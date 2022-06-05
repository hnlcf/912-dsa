#pragma once

#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <string>

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
                std::string msg = "%s: %d\n";
                msg += format;
                ContainerException::throwOutOfRangeFmt(msg.c_str(), file, line, n, size);
                exit(1);
            }
        }
    };
}
