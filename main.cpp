#include <format>
#include <iostream>

#include <glm/common.hpp>
#include "CrystalSpatial/space.h"

#include <CrystalSpatial/spatial.h>

int main() {
  crystal::spatial::Space<3, float> space;
  auto root_ss = space.RootSubSpace();
  root_ss->Trans() = crystal::spatial::Trans<3, float>{
    2, 0, 0,
    0, 2, 0,
    0, 0, 2
  };
  auto child_ss = root_ss->CreateChild(crystal::spatial::Trans<3, float>{
      1,
      2,
      3,
      4,
      5,
      6,
      7,
      8,
      9,
  });
  std::cout << std::format("Root SS Trans: {}", root_ss->RelTrans());
  std::cout << std::format("Child SS RelTrans: {}", child_ss->RelTrans());
  std::cout << std::format("Child SS AbsTrans: {}", child_ss->AbsTrans());
  auto pos = root_ss->CreatePosition({1.0, 2.0, 3.0});
  std::cout << std::format("Pos Rel: {}", pos->Rel());
  std::cout << std::format("Pos Abs: {}", pos->Abs());
  auto cluster = child_ss->CreateCluster({{1, 1, 1}});
  for (auto v : cluster->RelVecs())
    std::cout << std::format("Cluster Rel: {}", v);
  for (auto v : cluster->AbsVecs())
    std::cout << std::format("Cluster Abs: {}", v);
  auto space_idx = root_ss->SpaceIdx();
  return 0;
}