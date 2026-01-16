#ifndef CRYSTALSPATIAL_PRIMITIVE_TRANSFORMATION_H_
#define CRYSTALSPATIAL_PRIMITIVE_TRANSFORMATION_H_

#include <ostream>
#include <format>

#include "glm/ext/matrix_transform.hpp"

#include "mat3f.h"
#include "vec2f.h"
#include "vec3f.h"

namespace crystal::spatial {
struct trans : public mat3f {
  trans(const mat3f& mat = glm::identity<mat3f>()) : mat3f(mat) {}
  vec2f operator()(const vec2f& vec) const {
    vec3f tmp = (*this * vec3f{vec.x, vec.y, 1.0f});
    return vec2f{tmp.x, tmp.y};
  }
  trans operator()(const trans& t) const {
    return *this * t;
  }
  trans& Translate(vec2f offset) {
    (*this)[0][2] += offset[0];
    (*this)[1][2] += offset[1];
    return *this;
  }
  trans& Rotate(float angle) {
    (*this) = mat3f{
      glm::cos(angle), -glm::sin(angle), 0.0f,
      glm::sin(angle), glm::cos(angle), 0.0f,
      0.0f, 0.0f, 1.0f
    } * (*this);
    return *this;
  }
};

inline std::ostream& operator<<(std::ostream& os, const trans& trans) {
  os << std::format("trans({}):\n\t[{}, {}, {}]\n\t[{}, {}, {}]\n\t[{}, {}, {}]",
                    reinterpret_cast<const void*>(&trans),
                    trans[0][0], trans[0][1], trans[0][2],
                    trans[1][0], trans[1][1], trans[1][2],
                    trans[2][0], trans[2][1], trans[2][2]);
  return os;
}
} // namespace crystal::spatial

#endif
