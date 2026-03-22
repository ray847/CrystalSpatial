#ifndef CRYSTALSPAIAL_CONST_SPACE_INDEX_H_
#define CRYSTALSPAIAL_CONST_SPACE_INDEX_H_

#include "space.h"

namespace crystal::spatial {

template <typename SpaceDef>
class CSpaceIdx {
 public:
  using Space = Space<SpaceDef>;

  /* Accessor */
  const auto& operator*() const {
    return space_;
  }
  const auto& operator->() const {
    return &space_;
  }

 private:
  const Space& space_;

  /* Constructor */
  CSpaceIdx(const Space& space) : space_(space) {}
};

} // namespace crystal::spatial

#endif