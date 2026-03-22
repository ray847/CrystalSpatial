#ifndef CRYSTALSPATIAL_TRANSFORMATION_TRS_QUAT_H_
#define CRYSTALSPATIAL_TRANSFORMATION_TRS_QUAT_H_

#include <cstddef>

#include <ranges>

#include <glm/detail/qualifier.hpp>
#include <glm/ext/quaternion_float.hpp>
#include <glm/gtc/quaternion.hpp>
#include "glm/ext/quaternion_trigonometric.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_operation.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "CrystalSpatial/transformation.h"
#include "affine.h"

namespace crystal::spatial {

struct TRSQuatTrans {
  static constexpr std::size_t kDim = 3;
  static constexpr bool kComplete = false;
  using CompleteTrans = AffineTrans<3, float>;
  using Vec = glm::vec3;
  using Quat = glm::quat;

  Vec translate = {0, 0, 0};
  Vec scale = {1, 1, 1};
  Quat rotation = {1, 0, 0, 0};

  constexpr void IncrScale(const Vec& v) {
    scale = scale * v;
  }
  constexpr void IncrRotate(float angle, const Vec& axis) {
    rotation = glm::angleAxis(angle, axis) * rotation;
  }
  void IncrTranslate(const Vec& v) {
    translate += v;
  }
  Vec operator()(const Vec& v) const {
    return translate + (rotation * (scale * v));
  }
  template <typename VecView>
  auto operator()(const VecView& vv) const {
    auto mat = Matrix();
    return vv | std::views::transform([mat](const Vec& v) -> glm::vec3 {
             return mat * glm::vec4{v, 1};
           });
  }
  CompleteTrans operator()(const TRSQuatTrans& child) const {
    return {Matrix() * child.Matrix()};
  }
  operator CompleteTrans() const { return {Matrix()}; }
  glm::mat4 Matrix() const {
    glm::mat4 t = glm::translate(glm::mat4(1.0f), translate);
    glm::mat4 r = glm::mat4_cast(rotation);
    glm::mat4 s = glm::scale(glm::mat4(1.0f), scale);
    return t * r * s;
  }
};

static_assert(AnyTrans<TRSQuatTrans>);

} // namespace crystal::spatial

#endif