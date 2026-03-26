#ifndef CRYSTALSPAIAL_SUBSPACE_INDEX_H_
#define CRYSTALSPAIAL_SUBSPACE_INDEX_H_

#include <cstddef>
#include <utility>

#include "impl/subspace.h"
#include "space.h"
#include "transformation.h"

namespace crystal::spatial {

/* Forward Declaration */
template <typename SpaceDef>
class SpaceIdx;
template <AnyObj Obj, typename SpaceDef>
class ObjIdx;

template <typename SpaceDef>
class SubSpaceIdx {
 public:
  using SubSpaceImpl = impl::SubSpace<SpaceDef>;
  using Space = Space<SpaceDef>;
  using SpaceIdx_t = SpaceIdx<SpaceDef>;

  /* Functions */
  [[nodiscard]] SubSpaceIdx CreateChild(
      const typename SpaceDef::Trans& trans = {}) {
    return space_.CreateSubSpace(subspace_, trans);
  }
  template <AnyObj Obj, typename ...Args>
  [[nodiscard]] ObjIdx<Obj, SpaceDef> CreateObj(Args&&... args) {
    return space_.template CreateObj<Obj>(subspace_,
                                          std::forward<Args>(args)...);
  }
  SpaceIdx_t SpaceIdx() { return {space_}; }
  const SpaceIdx_t SpaceIdx() const { return {space_}; }

  /* Modifiers */
  void SetParent(const SubSpaceIdx& other) {
    assert(other.space_ == space_ && "Cannot set parent from another space.");
    Impl().parent = other.subspace_;
  }
  /* Accessors */
  SubSpaceIdx Parent() const { return {space_, Impl().parent}; }
  auto& Trans() { return Impl().trans; }
  auto Trans() const { return Impl().trans; }
  bool IsRoot() const { return subspace_ == 0; }
  CompleteTrans<typename SpaceDef::Trans> RelTrans() const {
    return Impl().trans;
  }
  CompleteTrans<typename SpaceDef::Trans> AbsTrans() const {
    CompleteTrans<typename SpaceDef::Trans> trans = RelTrans();
    std::size_t curr = subspace_;
    while (curr != 0) {
      curr = space_.subspaces_[curr].parent;
      trans = static_cast<CompleteTrans<typename SpaceDef::Trans>>(
          space_.subspaces_[curr].trans)(trans);
    }
    return trans;
  }

 private:
  friend Space;
  template <AnyObj Obj, typename>
  friend class ObjIdx;

  Space& space_;
  std::size_t subspace_;

  /* Constructor */
  SubSpaceIdx(Space& space, std::size_t idx) : space_(space), subspace_(idx) {}

  /* Accessor */
  SubSpaceImpl& Impl() { return space_.subspaces_[subspace_]; }
  const SubSpaceImpl& Impl() const { return space_.subspaces_[subspace_]; }
};

} // namespace crystal::spatial

#endif