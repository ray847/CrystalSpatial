#ifndef CRYSTALSPATIAL_OBJECT_INDEX_H_
#define CRYSTALSPATIAL_OBJECT_INDEX_H_

#include <cstddef>

#include "space.h"

namespace crystal::spatial {

/* Forward Declaration */
template <typename SpaceDef>
class SpaceIdx;
template <typename SpaceDef>
class SubSpaceIdx;

template <AnyObj Obj, typename SpaceDef>
class ObjIdx {
 public:
  using Space = Space<SpaceDef>;
  using SpaceIdx_t = SpaceIdx<SpaceDef>;
  using SubSpaceIdx_t = SubSpaceIdx<SpaceDef>;

  /* Functions */
  auto Rel() const {
    return Get();
  }
  auto Abs() const {
    auto abs_trans = SubSpaceIdx().AbsTrans();
    return abs_trans(Get());
  }
  SubSpaceIdx_t SubSpaceIdx() { return {space_, Wrapper().parent_}; }
  const SubSpaceIdx_t SubSpaceIdx() const {
    return {space_, Wrapper().parent_};
  }
  SpaceIdx_t SpaceIdx() { return {space_}; }
  const SpaceIdx_t SpaceIdx() const { return {space_}; }

  /* Accessor */
  auto& Get() { return Wrapper().obj_; }
  const auto& Get() const { return Wrapper().obj_; }
  Obj& operator*() { return Get(); }
  const Obj& operator*() const { return Get(); }
  Obj* operator->() { return &Get(); }
  const Obj* operator->() const { return &Get(); }

 private:
  friend Space;

  Space& space_;
  std::size_t idx_;

  /* Constructor */
  ObjIdx(Space& space, std::size_t idx) : space_(space), idx_(idx) {}

  /* Accessor */
  auto& Wrapper() {
    auto& container = space_.template ObjContainer<Obj>();
    return container[idx_];
  }
  const auto& Wrapper() const {
    auto& container = space_.template ObjContainer<Obj>();
    return container[idx_];
  }
};

} // namespace crystal::spatial

#endif