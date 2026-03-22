#ifndef CRYSTALSPATIAL_CONST_OBJECT_INDEX_H_
#define CRYSTALSPATIAL_CONST_OBJECT_INDEX_H_

#include <cstddef>

#include "space.h"

namespace crystal::spatial {

/* Forward Declaration */
template <typename SpaceDef>
class SpaceIdx;
template <typename SpaceDef>
class SubSpaceIdx;

template <AnyObj Obj, typename SpaceDef>
class CObjIdx {
 public:
  using Space = Space<SpaceDef>;
  using SpaceIdx_t = SpaceIdx<SpaceDef>;
  using SubSpaceIdx_t = SubSpaceIdx<SpaceDef>;

  /* Functions */
  auto Rel() const { return Get(); }
  auto Abs() const {
    auto abs_trans = SubSpaceIdx().AbsTrans();
    return abs_trans(Get());
  }
  const SubSpaceIdx_t SubSpaceIdx() const {
    return {space_, Wrapper().parent_};
  }
  const SpaceIdx_t SpaceIdx() const { return {space_}; }

  /* Accessor */
  const auto& Get() const { return Wrapper().obj_; }
  const Obj& operator*() const { return Get(); }
  const Obj* operator->() const { return &Get(); }

 private:
  friend Space;

  const Space& space_;
  std::size_t idx_;

  /* Constructor */
  CObjIdx(const Space& space, std::size_t idx) : space_(space), idx_(idx) {}

  /* Accessor */
  const auto& Wrapper() const {
    auto& container = space_.template ObjContainer<Obj>();
    return container[idx_];
  }
};

} // namespace crystal::spatial

#endif