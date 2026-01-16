#ifndef CRYSTALSPATIAL_PRIMITIVE_MAT3F_H_
#define CRYSTALSPATIAL_PRIMITIVE_MAT3F_H_

#include <format>
#include <ostream>

#include "glm/ext/matrix_float3x3.hpp"

namespace crystal::spatial {
using mat3f = glm::mat3x3;

inline std::ostream& operator<<(std::ostream& os, const mat3f& mat) {
  os << std::format("mat3f({}):\n\t[{}, {}, {}]\n\t[{}, {}, {}]\n\t[{}, {}, {}]",
                    reinterpret_cast<const void*>(&mat),
                    mat[0][0], mat[0][1], mat[0][2],
                    mat[1][0], mat[1][1], mat[1][2],
                    mat[2][0], mat[2][1], mat[2][2]);
  return os;
}
} // namespace crystal::spatial

#endif
