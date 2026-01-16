#ifndef CRYSTALSPATIAL_PRIMITIVE_MAT2F_H_
#define CRYSTALSPATIAL_PRIMITIVE_MAT2F_H_

#include <format>
#include <ostream>

#include "glm/ext/matrix_float2x2.hpp"

namespace crystal::spatial {
using mat2f = glm::mat2x2;

inline std::ostream& operator<<(std::ostream& os, const mat2f& mat) {
  os << std::format("mat2f({}):\n\t[{}, {}]\n\t[{}, {}]",
                    reinterpret_cast<const void*>(&mat), mat[0][0], mat[0][1],
                    mat[0][1], mat[1][1]);
  return os;
}
} // namespace crystal::spatial

#endif
