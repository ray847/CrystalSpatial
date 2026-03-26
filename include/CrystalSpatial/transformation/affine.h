#ifndef CRYSTALSPATIAL_TRANSFORMATION_AFFINE_H_
#define CRYSTALSPATIAL_TRANSFORMATION_AFFINE_H_

#include <ranges>

#include <glm/ext/matrix_float3x3.hpp>

#include "CrystalSpatial/transformation.h"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/vector_float4.hpp"

namespace crystal::spatial {

template <std::size_t kDim, typename T>
struct AffineTrans;

template <>
struct AffineTrans<3, float> {
  static constexpr bool kComplete = true;
  using Vec = glm::vec3;
  using Mat = glm::mat4;

  Mat mat;

  Vec operator()(const Vec& v) const {
    return mat * glm::vec4{v, 1};
  }
  template <std::ranges::range VecView>
  auto operator()(const VecView& vv) const {
    return vv | std::views::transform([&](const Vec& v) -> glm::vec3 {
             return mat * glm::vec4{v, 1};
           });
  }
  AffineTrans operator()(const AffineTrans& t) const { return {mat * t.mat}; }
};
static_assert(AnyTrans<AffineTrans<3, float>>);

}

#endif