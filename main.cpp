#include <format>
#include <iostream>

#include <glm/common.hpp>

#include <CrystalSpatial/spatial.h>

int main() {
  using SpaceDef =
      crystal::spatial::SpaceDef<crystal::spatial::TRSQuatTrans, glm::vec3,
                                 std::vector<glm::vec3>>;
  crystal::spatial::Space<SpaceDef> space;
  auto root_ss = space.RootSubSpace();
  root_ss.Trans().IncrScale({1, 2, 3});
  std::cout << std::format("Root SS: {}", root_ss.Trans().Matrix());
  auto child_ss = root_ss.CreateChild();
  child_ss.Trans().IncrRotate(2, {1, 1, 1});
  std::cout << std::format("Child SS: {}", child_ss.Trans().Matrix());
  auto vec = root_ss.CreateObj<glm::vec3>(1, 2, 3);
  std::cout << std::format("Vec: {}", *vec);
  std::cout << std::format("Vec Rel: {}", vec.Rel());
  std::cout << std::format("Vec Abs: {}", vec.Abs());
  auto vecs = child_ss.CreateObj<std::vector<glm::vec3>>();
  vecs->push_back({4, 5, 6});
  auto rel = vecs.Rel();
  auto abs = vecs.Abs();
  std::cout << std::format("Vecs Rel: {}", rel[0]);
  std::cout << std::format("Vecs Abs: {}", abs[0]);
  return 0;
}