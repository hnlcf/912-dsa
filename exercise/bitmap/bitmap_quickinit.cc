#include <bitmap_quickinit.h>

inline bool dsa::BitmapQuickInit::IsValid(size_type r) const {
  return r >= 0 and r < m_top;
}

inline bool dsa::BitmapQuickInit::IsErase(size_type r) const {
  return IsValid(m_rank[r]) and ((m_stack[m_rank[r]] + r + 1) == 0);
}

inline bool dsa::BitmapQuickInit::IsRecord(size_type r) const {
  return IsValid(m_rank[r]) and (m_stack[m_rank[r]] == r);
}

inline void dsa::BitmapQuickInit::Set(size_type r) {
  if (IsRecord(r)) {
    return;
  }
  if (!IsErase(r)) {
    m_rank[r] = m_top;
    m_top++;
  }
  m_stack[m_rank[r]] = r;
}

inline void dsa::BitmapQuickInit::Clear(size_type r) {
  if (IsRecord(r)) {
    m_stack[m_rank[r]] = -1 - r;
  }
}

inline void dsa::BitmapQuickInit::Reset() { m_top = 0; }
