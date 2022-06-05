#pragma once

#include "AutoHeader.hpp"
#include <cstdint>

namespace dsa {
    class BitmapQuickInit {
    private:
        size_type  m_size;   // size of Bitmap
        size_type *m_rank;   // store the ranks of all elements in the stack
        size_type *m_stack;  // store map
        size_type  m_top;    // point to the top of stack

    protected:
        /// Verify the rank `r` is valid in the current stack
        /// r is in [0, top) or not
        inline bool isValid(size_type r) const;

        /// Verify the rank `r` is erased in the stack
        inline bool isErase(size_type r) const;

        /// Verify the rank `r` is recorded already or not in the stack
        inline bool isRecord(size_type r) const;

    public:
        explicit BitmapQuickInit(size_type n = 8)
          : m_size(n), m_rank(new size_type[n]), m_stack(new size_type[n]), m_top(0) {
        }

        ~BitmapQuickInit() {
            delete[] m_rank;
            delete[] m_stack;
        }

        /// Set the check bit
        /// use stack[rank[r]] = r
        inline void set(size_type r);

        /// Clear the check bit
        /// use stack[rank[r]] = -1-r
        inline void clear(size_type r);

        /// Reset the Bitmap
        /// use top = 0
        inline void reset();
    };
}
