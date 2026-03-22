#ifndef CRYSTALSPAIAL_SUBSPACE_INDEX_H_
#define CRYSTALSPAIAL_SUBSPACE_INDEX_H_

#include <cstddef>
#include <vector>

#include "impl/subspace.h"
#include "space.h"
#include "transformation.h"

namespace crystal::spatial {

/* Forward Declaration */
template <std::size_t kDim, typename T, AnyTrans Trans>
class SpaceIdx;
template <std::size_t kDim, typename T, AnyTrans Trans>
class PositionIdx;
template <std::size_t kDim, typename T, AnyTrans Trans>
class ClusterIdx;

template <std::size_t kDim, typename T, AnyTrans Transformation>
class SubSpaceIdx {
 public:
  using SubSpaceImpl = impl::SubSpace<kDim, T, Transformation>;
  using Space = Space<kDim, T, Transformation>;
  using SpaceIdx = SpaceIdx<kDim, T, Transformation>;
  using PositionIdx = PositionIdx<kDim, T, Transformation>;
  using ClusterIdx = ClusterIdx<kDim, T, Transformation>;
  using Vec = glm::vec<kDim, T>;
  class SubSpaceProxy {
   public:
    /* Constructor */
    SubSpaceProxy(Space& space, std::size_t subspace)
        : space_(space), subspace_(subspace) {}

    /* Functions */
    SubSpaceIdx CreateChild(const Transformation& trans = {}) {
      return space_.CreateSubSpace(subspace_, trans);
    }
    PositionIdx CreatePosition(const Vec& vec = {}) {
      return space_.CreatePosition(subspace_, vec);
    }
    ClusterIdx CreateCluster(const std::vector<Vec>& vecs = {}) {
      return space_.CreateCluster(subspace_, vecs);
    }
    SpaceIdx SpaceIdx() { return {space_}; }

    /* Modifiers */
    void SetParent(const SubSpaceIdx& other) {
      assert(other.proxy_.space_ == space_ &&
             "Cannot set parent from another space.");
      Impl().parent = other.proxy_.subspace_;
    }
    /* Accessors */
    SubSpaceIdx Parent() const { return {space_, Impl().parent}; }
    auto& Trans() { return Impl().trans; }
    auto Trans() const { return Impl().trans; }
    bool IsRoot() const { return subspace_ == 0; }
    auto RelTrans() const { return Impl().trans; }
    auto AbsTrans() const {
      auto trans = RelTrans();
      std::size_t curr = subspace_;
      while (curr != 0) {
        curr = space_.subspaces_[curr].parent;
        trans = trans(space_.subspaces_[curr].trans);
      }
      return trans;
    }

   private:
    Space& space_;
    std::size_t subspace_;

    SubSpaceImpl& Impl() { return space_.subspaces_[subspace_]; }
    const SubSpaceImpl& Impl() const { return space_.subspaces_[subspace_]; }
  };

  /* Accessor */
  auto& operator*() { return proxy_; }
  const auto& operator*() const { return proxy_; }
  auto operator->() { return &proxy_; }
  const auto operator->() const { return &proxy_; }
  /* Decay to index. */
  operator std::size_t() { return proxy_.subspace_; }

 private:
  friend Space;
  friend PositionIdx;
  friend ClusterIdx;

  SubSpaceProxy proxy_;

  /* Constructor */
  SubSpaceIdx(Space& space, std::size_t idx) : proxy_{space, idx} {}
};

} // namespace crystal::spatial

#endif