#ifndef CRYSTAL_PRIMITIVE_CONSTANTS_H_
#define CRYSTAL_PRIMITIVE_CONSTANTS_H_

#include "glm/ext/matrix_transform.hpp"

namespace crystal::spatial {
template<typename mat>
consteval mat identity() {
  return glm::identity<mat>();
}
} // namespace crystal::spatial

#endif