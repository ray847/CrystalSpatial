#ifndef CRYSTALSPATIAL_CLUSTER_INDEX_H_
#define CRYSTALSPATIAL_CLUSTER_INDEX_H_

#include <cstddef>

#include <ranges>

#include "impl/cluster.h"
#include "transformation.h"
#include "space.h"

namespace crystal::spatial {

/* Forward Declaration */
template <std::size_t dim, typename T, AnyTrans Trans>
class SpaceIdx;
template <std::size_t dim, typename T, AnyTrans Trans>
class SubSpaceIdx;

template <std::size_t dim, typename T, AnyTrans Trans>
class ClusterIdx {
 public:
  using ClusterImpl = impl::Cluster<dim, T>;
  using Space = Space<dim, T, Trans>;
  using SpaceIdx_t = SpaceIdx<dim, T, Trans>;
  using SubSpaceIdx_t = SubSpaceIdx<dim, T, Trans>;
  using Vec = glm::vec<dim, T>;
  class ClusterProxy {
   public:
    /* Constructor */
    ClusterProxy(Space& space, std::size_t subspace, std::size_t cluster)
        : space_(space), subspace_(subspace), cluster_(cluster) {}
    /* Functions */
    auto& Vecs() { return Impl().vecs; }
    const auto& Vecs() const { return Impl().vecs; }
    const auto& RelVecs() const { return Vecs(); }
    auto AbsVecs() const {
      auto abs_trans = SubSpaceIdx()->AbsTrans();
      return Vecs() | std::views::transform(
                        [abs_trans](const Vec& v) { return abs_trans(v); });
    }
    SubSpaceIdx_t SubSpaceIdx() { return {space_, subspace_}; }
    const SubSpaceIdx_t SubSpaceIdx() const { return {space_, subspace_}; }
    SpaceIdx_t SpaceIdx() { return {space_}; }
    const SpaceIdx_t SpaceIdx() const { return {space_}; }

   private:
    Space& space_;
    std::size_t subspace_, cluster_;

    auto& Impl() { return space_.clusters_[cluster_]; }
    const auto& Impl() const { return space_.clusters_[cluster_]; }
  };

  /* Accessor */
  auto& operator*() { return proxy_; }
  const auto& operator*() const { return proxy_; }
  auto operator->() { return &proxy_; }
  const auto operator->() const { return &proxy_; }

 private:
  friend Space;

  ClusterProxy proxy_;

  /* Constructor */
  ClusterIdx(Space& space, std::size_t subspace, std::size_t position)
      : proxy_(space, subspace, position) {}
};

} // namespace crystal::spatial

#endif