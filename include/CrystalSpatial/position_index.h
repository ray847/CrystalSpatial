#ifndef CRYSTALSPATIAL_POSITION_INDEX_H_
#define CRYSTALSPATIAL_POSITION_INDEX_H_

#include <cstddef>

#include "impl/position.h"
#include "space.h"

namespace crystal::spatial {

/* Forward Declaration */
template <std::size_t dim, typename T, AnyTrans Trans>
class SpaceIdx;
template <std::size_t dim, typename T, AnyTrans Trans>
class SubSpaceIdx;

template <std::size_t kDim, typename T, AnyTrans Trans>
class PositionIdx {
 public:
  using PositionImpl = impl::Position<kDim, T>;
  using Space = Space<kDim, T, Trans>;
  using SpaceIdx_t = SpaceIdx<kDim, T, Trans>;
  using SubSpaceIdx_t = SubSpaceIdx<kDim, T, Trans>;
  class PositionProxy {
   public:
    /* Constructor */
    PositionProxy(Space& space, std::size_t subspace, std::size_t position)
        : space_(space), subspace_(subspace), position_(position) {}
    /* Functions */
    auto& Vec() { return Impl().vec; }
    auto Vec() const { return Impl().vec; }
    auto Rel() const { return Vec(); }
    auto Abs() const {
      auto abs_trans = SubSpaceIdx()->AbsTrans();
      auto vec = Vec();
      return abs_trans(vec);
    }
    SubSpaceIdx_t SubSpaceIdx() { return {space_, subspace_}; }
    const SubSpaceIdx_t SubSpaceIdx() const { return {space_, subspace_}; }
    SpaceIdx_t SpaceIdx() { return {space_}; }
    const SpaceIdx_t SpaceIdx() const { return {space_}; }

   private:
    Space& space_;
    std::size_t subspace_, position_;

    auto& Impl() { return space_.positions_[position_]; }
    const auto& Impl() const { return space_.positions_[position_]; }
  };

  /* Accessor */
  auto& operator*() { return proxy_; }
  const auto& operator*() const { return proxy_; }
  auto operator->() { return &proxy_; }
  const auto operator->() const { return &proxy_; }

 private:
  friend Space;

  PositionProxy proxy_;

  /* Constructor */
  PositionIdx(Space& space, std::size_t subspace, std::size_t position)
      : proxy_(space, subspace, position) {}
};

} // namespace crystal::spatial

#endif