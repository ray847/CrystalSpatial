#ifndef CRYSTALSPAIAL_CONST_SUBSPACE_INDEX_H_
#define CRYSTALSPAIAL_CONST_SUBSPACE_INDEX_H_

#include <cstddef>

#include "impl/subspace.h"
#include "space.h"
#include "transformation.h"

namespace crystal::spatial {

/* Forward Declaration */
template <typename SpaceDef>
class CSpaceIdx;
template <AnyObj Obj, typename SpaceDef>
class ObjIdx;

template <typename SpaceDef>
class CSubSpaceIdx {
 public:
  using SubSpaceImpl = impl::SubSpace<SpaceDef>;
  using Space = Space<SpaceDef>;
  using CSpaceIdx_t = CSpaceIdx<SpaceDef>;

  /* Functions */
  CSpaceIdx_t SpaceIdx() const { return {space_}; }

  /* Accessors */
  CSubSpaceIdx Parent() const { return {space_, Impl().parent}; }
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
  template <AnyObj Obj, typename>
  friend class CObjIdx;

  const Space& space_;
  std::size_t subspace_;

  /* Constructor */
  CSubSpaceIdx(const Space& space, std::size_t idx)
      : space_(space), subspace_(idx) {}

  /* Accessor */
  const SubSpaceImpl& Impl() const { return space_.subspaces_[subspace_]; }
};

} // namespace crystal::spatial

#endif