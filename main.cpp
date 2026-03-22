#include <format>
#include <iostream>

#include <glm/common.hpp>
#include "CrystalSpatial/space.h"
#include "CrystalSpatial/transformation/trs_quat.h"

#include <CrystalSpatial/spatial.h>

int main() {
  crystal::spatial::Space<3, float, crystal::spatial::TRSQuatTrans> space;
  auto root_ss = space.RootSubSpace();
  root_ss->Trans().IncrScale({1, 2, 3});
  root_ss->Trans().IncrTranslate({-5, -6, -7});
  auto child_ss = root_ss->CreateChild();
  child_ss->Trans().IncrRotate(2, {1, 1, 1});
  std::cout << std::format("Root SS Trans: {}", root_ss->RelTrans().Matrix());
  std::cout << std::format("Child SS RelTrans: {}",
                           child_ss->RelTrans().Matrix());
  std::cout << std::format("Child SS AbsTrans: {}",
                           child_ss->AbsTrans().Matrix());
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