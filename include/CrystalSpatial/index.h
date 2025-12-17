#ifndef CRYSTALSPATIAL_INDEX_H_
#define CRYSTALSPATIAL_INDEX_H_

#include <cstdint> // uint64_t

#include <CrystalBase/strict_index.h> // StrictIdx

namespace crystal::spatial {
/* Tags (for the index types) */
struct SpatialTag {};
struct SpaceTag {};
struct SubSpaceTag {};
struct VecTag {};

/* Strict Index Types */
using SpaceIdx = StrictIdx<SpaceTag, uint16_t>;
using SubSpaceIdx = StrictIdx<SpatialTag, uint16_t>;
using VecIdx = StrictIdx<VecTag, uint32_t>;

struct SpatialIdx : public StrictIdx<SpatialTag, uint64_t> {
  /* Constructor */
  SpatialIdx(SpaceIdx space_idx,
             SubSpaceIdx subspace_idx = {},
             VecIdx vec_idx = {}):
    StrictIdx<SpatialTag, uint64_t>(
      (uint64_t)space_idx << (sizeof(SubSpaceIdx) * 8 + sizeof(VecIdx) * 8) |
      (uint64_t)subspace_idx << sizeof(VecIdx) * 8 |
      (uint64_t)vec_idx
    ) {}
  SpatialIdx(SubSpaceIdx subspace_idx, VecIdx vec_idx = {}):
    SpatialIdx(SpaceIdx{}, subspace_idx, vec_idx) {}
  SpatialIdx(VecIdx vec_idx) : SpatialIdx(SpaceIdx{}, SubSpaceIdx{}, vec_idx) {}
  SpatialIdx() : SpatialIdx(SpaceIdx{}, SubSpaceIdx{}, VecIdx{}) {}
  /* Type Conversions */
  operator SpaceIdx() const {
    return SpaceIdx(value >> (sizeof(SubSpaceIdx) + sizeof(VecIdx)) * 8);
  }
  operator SubSpaceIdx() const {
    return SubSpaceIdx(value >> sizeof(VecIdx) * 8);
  }
  operator VecIdx() const {
    return VecIdx(value);
  }
};

static_assert(
sizeof(SpatialIdx) == sizeof(SpaceIdx) + sizeof(SubSpaceIdx) + sizeof(VecIdx),
"Spatial index should be the sum of the segments."
);
} // namespace crystal::spatial

#endif
