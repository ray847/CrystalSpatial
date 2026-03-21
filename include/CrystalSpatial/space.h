#ifndef CRYSTALSPATIAL_SPACE_H_
#define CRYSTALSPATIAL_SPACE_H_

#include <cassert>

#include <vector>

#include <glm/ext/matrix_transform.hpp>

#include "impl/position.h"
#include "impl/subspace.h"
#include "impl/cluster.h"
#include "transformation.h"

namespace crystal::spatial {

template <std::size_t kDim, typename T>
class SubSpaceIdx;
template <std::size_t kDim, typename T>
class PositionIdx;
template <std::size_t kDim, typename T>
class ClusterIdx;

template <std::size_t kDim, typename T>
class Space {
 public:
  using SubSpaceImpl = impl::SubSpace<kDim, T>;
  using PositionImpl = impl::Position<kDim, T>;
  using ClusterImpl = impl::Cluster<kDim, T>;
  using SubSpaceIdx = SubSpaceIdx<kDim, T>;
  using PositionIdx = PositionIdx<kDim, T>;
  using ClusterIdx = ClusterIdx<kDim, T>;
  using Trans = Trans<kDim, T>;
  using Vec = glm::vec<kDim, T>;

  /* Functions */
  SubSpaceIdx RootSubSpace() { return {*this, 0}; }

 private:
  friend SubSpaceIdx;
  friend PositionIdx;
  friend ClusterIdx;

  std::vector<SubSpaceImpl> subspaces_{
      SubSpaceImpl{.parent = 0, .trans = glm::identity<Trans>()}};
  std::vector<PositionImpl> positions_;
  std::vector<ClusterImpl> clusters_;

  SubSpaceIdx CreateSubSpace(std::size_t parent, const Trans& trans) {
    assert(parent < subspaces_.size() && "Invalid subspace parent.");
    subspaces_.push_back(SubSpaceImpl{.parent = parent, .trans = trans});
    return {*this, subspaces_.size() - 1};
  }
  PositionIdx CreatePosition(std::size_t subspace, const Vec& vec) {
    assert(subspace < subspaces_.size() && "Invalid subspace parent.");
    positions_.push_back(PositionImpl{.subspace = subspace, .vec = vec});
    return {*this, subspace, positions_.size() - 1};
  }
  ClusterIdx CreateCluster(std::size_t subspace, const std::vector<Vec>& vecs) {
    assert(subspace < subspaces_.size() && "Invalid subspace parent.");
    clusters_.push_back(ClusterImpl{.subspace = subspace, .vecs = vecs});
    return {*this, subspace, clusters_.size() - 1};
  }
};

} // namespace crystal::spatial

#endif