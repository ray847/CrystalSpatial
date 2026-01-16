#ifndef CRYSTALSPATIAL_PRIMITIVE_VEC3F_H_
#define CRYSTALSPATIAL_PRIMITIVE_VEC3F_H_

#include <format>
#include <ostream>

#include "glm/ext/vector_float3.hpp"

namespace crystal::spatial {
using vec3f = glm::vec3;

} // namespace crystal::spatial

namespace glm {
inline std::ostream& operator<<(std::ostream& os, const glm::vec3& vec) {
  os << std::format("vec3f({}): <{}, {}, {}>",
                    reinterpret_cast<const void*>(&vec), vec.x, vec.y, vec.z);
  return os;
}
} // namespace glm

#endif
