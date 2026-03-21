#ifndef CRYSTALSPAIAL_SPACE_INDEX_H_
#define CRYSTALSPAIAL_SPACE_INDEX_H_

#include "space.h"

namespace crystal::spatial {

template <std::size_t dim, typename T>
class SpaceIdx {
 public:
  using Space = Space<dim, T>;

  /* Constructor */
  SpaceIdx(Space& space) : space_(space) {}

  /* Accessor */
  auto& operator*() {
    return space_;
  }
  const auto& operator*() const {
    return space_;
  }
  auto& operator->() {
    return &space_;
  }
  const auto& operator->() const {
    return &space_;
  }

 private:
  Space& space_;
};

} // namespace crystal::spatial

#endif