#include <gtest/gtest.h>
#include <CrystalSpatial/index.h>
#include <CrystalSpatial/space.h>

using namespace crystal::spatial;

TEST(SpatialIdxTest, CompositionAndDecomposition) {
  SpaceIdx sp_idx(1);
  SubSpaceIdx sub_idx(2);
  VecIdx vec_idx(3);

  SpatialIdx spatial_idx(sp_idx, sub_idx, vec_idx);

  EXPECT_EQ(static_cast<SpaceIdx>(spatial_idx), sp_idx);
  EXPECT_EQ(static_cast<SubSpaceIdx>(spatial_idx), sub_idx);
  EXPECT_EQ(static_cast<VecIdx>(spatial_idx), vec_idx);
}

TEST(SpatialIdxTest, PartialComposition) {
    SubSpaceIdx sub_idx(5);
    VecIdx vec_idx(10);
    
    SpatialIdx spatial_idx(sub_idx, vec_idx);
    
    EXPECT_EQ(static_cast<SpaceIdx>(spatial_idx), SpaceIdx{});
    EXPECT_EQ(static_cast<SubSpaceIdx>(spatial_idx), sub_idx);
    EXPECT_EQ(static_cast<VecIdx>(spatial_idx), vec_idx);
}

TEST(SpaceTest, CreateSubSpace) {
  Space space;
  auto idx1 = space.CreateSubSpace();
  auto idx2 = space.CreateSubSpace();
  
  EXPECT_NE(static_cast<uint64_t>(idx1), static_cast<uint64_t>(idx2));
}

TEST(SpaceTest, CreateVec) {
    Space space;
    auto idx1 = space.CreateVec(1.0f, 2.0f);
    auto idx2 = space.CreateVec(3.0f, 4.0f);

    EXPECT_NE(static_cast<uint64_t>(idx1), static_cast<uint64_t>(idx2));
}

TEST(SpaceTest, CreateSubSpaceWithParent) {
    Space space;
    auto parent_idx = space.CreateSubSpace();
    auto child_idx = space.CreateSubSpace(parent_idx);

    EXPECT_NE(static_cast<uint64_t>(parent_idx), static_cast<uint64_t>(child_idx));
}
