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

#include "CrystalSpatial/transformation.h"
#include "glm/ext/matrix_transform.hpp"

namespace crystal::spatial {

struct TRSQuatTrans {
  static constexpr std::size_t kDim = 3;
  using DType = float;
  using Vec = glm::vec3;
  using Quat = glm::quat;

  Vec translate = {0, 0, 0};
  Vec scale = {1, 1, 1};
  Quat rotation = {1, 0, 0, 0};

  constexpr void IncrScale(const Vec& v) {
    scale = scale * v;
  }
  constexpr void IncrRotate(DType angle, const Vec& axis) {
    rotation = glm::angleAxis(angle, axis) * rotation;
  }
  void IncrTranslate(const Vec& v) {
    translate += v;
  }
  Vec operator()(const Vec& v) const {
    return translate + rotation * scale * v;
  }
  template <typename VecView>
  auto operator()(const VecView& vv) const {
    auto mat = Matrix();
    return vv | std::views::transform([mat](const Vec& v) -> glm::vec3 {
             return mat * glm::vec4{v, 1};
           });
  }
  TRSQuatTrans operator()(const TRSQuatTrans& t) const {
    return TRSQuatTrans{.translate = translate + t.translate,
                        .scale = scale * t.scale,
                        .rotation = rotation * t.rotation};
  }
  glm::mat4 Matrix() const {
    return glm::translate(
        glm::mat4_cast(rotation) * glm::diagonal4x4(glm::vec4{scale, 1.0f}),
        translate);
  }
};

static_assert(AnyTrans<TRSQuatTrans>);

} // namespace crystal::spatial

#endif