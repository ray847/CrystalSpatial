#ifndef CRYSTALSPATIAL_SPACE_H_
#define CRYSTALSPATIAL_SPACE_H_

#include <memory_resource> // std::pmr

#include <CrystalBase/stable_vector.h>

#include "CrystalSpatial/vector.h" // Vec
#include "CrystalSpatial/subspace.h" // SubSpace
#include "CrystalSpatial/index.h" // SpatialIdx

namespace crystal::spatial {
class Space {
public:
  /* Constructor */
  Space():
    storage_(std::pmr::new_delete_resource()),
    subspaces_(&storage_),
    vecs_(&storage_) {}
  Space(const Space&) = delete;
  /* Assign Operator */
  Space& operator=(const Space& rhs) = delete;
  Space& operator=(Space&& rhs) = delete;
  /* Functions */
  template<typename...Args>
  [[nodiscard]] SpatialIdx CreateSubSpace(Args...args) {
    SubSpaceIdx idx = subspaces_.EmplaceBack(args...);
    return idx;
  }
  template<typename...Args>
  [[nodiscard]] SpatialIdx CreateSubSpace(SubSpaceIdx parent_idx, Args...args) {
    SubSpaceIdx idx = subspaces_.EmplaceBack(args...);
    subspaces_[idx].parent_ = parent_idx;
    subspaces_[parent_idx].children_.emplace_back(idx);
    return idx;
  }
  template<typename...Args>
  [[nodiscard]] SpatialIdx CreateSubSpace(SpatialIdx parent_idx, Args...args) {
    return CreateSubSpace(static_cast<SubSpaceIdx>(parent_idx), args...);
  }

  template<typename...Args>
  [[nodiscard]] SpatialIdx CreateVec(Args...args) {
    VecIdx idx = vecs_.EmplaceBack(args...);
    return idx;
  }
  template<typename...Args>
  [[nodiscard]] SpatialIdx CreateVec(SubSpaceIdx subspace_idx, Args...args) {
    VecIdx idx = subspaces_[subspace_idx].vecs_.EmplaceBack(args...);
    return idx;
  }
  template<typename...Args>
  [[nodiscard]] SpatialIdx CreateVec(SpatialIdx subspace_idx, Args...args) {
    return CreateVec(static_cast<SubSpaceIdx>(subspace_idx), args...);
  }
private:
  /* Variables */
  std::pmr::synchronized_pool_resource storage_;
  pmr::StableVector<SubSpace> subspaces_;
  pmr::StableVector<Vec> vecs_;
};
} // namespace crystal::spatial

#endif
