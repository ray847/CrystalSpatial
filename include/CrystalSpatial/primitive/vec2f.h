#ifndef CRYSTALSPATIAL_PRIMITIVE_VEC2F_H_
#define CRYSTALSPATIAL_PRIMITIVE_VEC2F_H_

#include <format>
#include <ostream>

#include "glm/ext/vector_float2.hpp"

namespace crystal::spatial {
using vec2f = glm::vec2;

} // namespace crystal::spatial

namespace glm {
inline std::ostream& operator<<(std::ostream& os, const glm::vec2& vec) {
  os << std::format("vec2f({}): <{}, {}>", reinterpret_cast<const void*>(&vec),
                    vec.x, vec.y);
  return os;
}
} // namespace glm

#endif