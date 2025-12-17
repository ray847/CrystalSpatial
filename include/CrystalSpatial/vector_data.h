#ifndef CRYSTALSPATIAL_VECTOR_DATA_H_
#define CRYSTALSPATIAL_VECTOR_DATA_H_

#include <cstddef> // size_t

#include <glm/detail/qualifier.hpp> // glm::vec
#include <glm/vec2.hpp> // glm::vec2

namespace crystal::spatial {

template<size_t kDim, typename T>
using VecData = glm::vec<kDim, T>;

using Vec2fData = glm::vec2;
} // namespace crystal::spatial

#endif
