#ifndef CRYSTALSPATIAL_SPACE_H_
#define CRYSTALSPATIAL_SPACE_H_

#include <cassert>

#include <vector>
#include <utility>
#include <ranges>

#include <glm/ext/matrix_transform.hpp>

#include "object.h"
#include "impl/subspace.h"

namespace crystal::spatial {

template <typename>
class SubSpaceIdx;
template <typename>
class CSubSpaceIdx;
template <AnyObj Obj, typename SpaceDef>
class ObjIdx;
template <AnyObj Obj, typename SpaceDef>
class CObjIdx;

template <typename SpaceDef>
class Space {
 public:
  using SubSpaceImpl = impl::SubSpace<SpaceDef>;
  using SubSpaceIdx = SubSpaceIdx<SpaceDef>;
  using CSubSpaceIdx = CSubSpaceIdx<SpaceDef>;

  /* Functions */
  [[nodiscard]] SubSpaceIdx RootSubSpace() { return {*this, 0}; }
  template <AnyObj Obj>
  [[nodiscard]] auto ObjView() {
    auto indices = std::views::iota(0uz, ObjContainer<Obj>().size());
    return indices | std::views::transform(
                         [this](std::size_t idx) -> ObjIdx<Obj, SpaceDef> {
                           return {*this, idx};
                         });
  }
  template <AnyObj Obj>
  [[nodiscard]] auto ObjView() const {
    auto indices = std::views::iota(0uz, ObjContainer<Obj>().size());
    return indices | std::views::transform(
                         [this](std::size_t idx) -> CObjIdx<Obj, SpaceDef> {
                           return {*this, idx};
                         });
  }

 private:
  friend SubSpaceIdx;
  friend CSubSpaceIdx;
  template <AnyObj Obj, typename>
  friend class ObjIdx;
  template <AnyObj Obj, typename>
  friend class CObjIdx;

  std::vector<SubSpaceImpl> subspaces_{
      SubSpaceImpl{.parent = 0, .trans = {}}};
  typename SpaceDef::ObjContainers objs_;

  SubSpaceIdx CreateSubSpace(std::size_t parent,
                             const typename SpaceDef::Trans& trans) {
    assert(parent < subspaces_.size() && "Invalid subspace parent.");
    subspaces_.push_back(SubSpaceImpl{.parent = parent, .trans = trans});
    return {*this, subspaces_.size() - 1};
  }
  template <AnyObj Obj, typename... Args>
  ObjIdx<Obj, SpaceDef> CreateObj(std::size_t subspace, Args&&... args) {
    assert(subspace < subspaces_.size() && "Invalid subspace parent.");
    auto& container = std::get<std::vector<ObjWrapper<Obj>>>(objs_);
    container.emplace_back(subspace, std::forward<Args>(args)...);
    return {*this, container.size() - 1};
  }
  template <AnyObj Obj>
  auto& ObjContainer() {
    return std::get<std::vector<ObjWrapper<Obj>>>(objs_);
  }
  template <AnyObj Obj>
  const auto& ObjContainer() const {
    return std::get<std::vector<ObjWrapper<Obj>>>(objs_);
  }
};

} // namespace crystal::spatial

#endif