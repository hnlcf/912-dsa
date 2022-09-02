#ifndef INC_912_DSA_DS_DICT_H_
#define INC_912_DSA_DS_DICT_H_

#include <ds/utils/autoheader.h>

namespace dsa {
template <class Key, class Value>
struct Dict {
 public:
  virtual size_type size() const                             = 0;
  virtual Value&    get(Key const& key) const                = 0;
  virtual bool      push(Key const& key, Value const& value) = 0;
  virtual bool      remove(Key const& key)                   = 0;
};
}  // namespace dsa

#endif
