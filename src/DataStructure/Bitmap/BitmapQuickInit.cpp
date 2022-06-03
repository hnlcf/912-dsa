#include "BitmapQuickInit.h"

inline bool
dsa::BitmapQuickInit::isValid(size_type r) const {
    return r >= 0 and r < m_top;
}

inline bool
dsa::BitmapQuickInit::isErase(size_type r) const {
    return isValid(m_rank[r]) and ((m_stack[m_rank[r]] + r + 1) == 0);
}

inline bool
dsa::BitmapQuickInit::isRecord(size_type r) const {
    return isValid(m_rank[r]) and (m_stack[m_rank[r]] == r);
}

inline void
dsa::BitmapQuickInit::set(size_type r) {
    if (isRecord(r)) {
        return;
    }
    if (!isErase(r)) {
        m_rank[r] = m_top;
        m_top++;
    }
    m_stack[m_rank[r]] = r;
}

inline void
dsa::BitmapQuickInit::clear(size_type r) {
    if (isRecord(r)) {
        m_stack[m_rank[r]] = -1 - r;
    }
}

inline void
dsa::BitmapQuickInit::reset() {
    m_top = 0;
}
