#pragma once

using Rank = int;

namespace dsa {
    class BitmapQuickInit {
    private:
        Rank *m_rank;   // store the ranks of all elements in the stack
        Rank  m_size;   // size of Bitmap
        Rank *m_stack;  // store map
        Rank  m_top;    // point to the top of stack

    protected:
        /// Verify the rank `r` is valid in the current stack
        /// r is in [0, top) or not
        inline bool isValid(Rank r) const;

        /// Verify the rank `r` is erased in the stack
        inline bool isErase(Rank r) const;

        /// Verify the rank `r` is recorded already or not in the stack
        inline bool isRecord(Rank r) const;

    public:
        explicit BitmapQuickInit(Rank n = 8)
          : m_size(n), m_rank(new Rank[n]), m_stack(new Rank[n]), m_top(0) {
        }

        ~BitmapQuickInit() {
            delete[] m_rank;
            delete[] m_stack;
        }

        /// Set the check bit
        /// use stack[rank[r]] = r
        inline void set(Rank r);

        /// Clear the check bit
        /// use stack[rank[r]] = -1-r
        inline void clear(Rank r);

        /// Reset the Bitmap
        /// use top = 0
        inline void reset();
    };
}
