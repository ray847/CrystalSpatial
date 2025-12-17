#ifndef CRYSTALSPATIAL_MATRIX_DATA_H_
#define CRYSTALSPATIAL_MATRIX_DATA_H_

#include <glm/detail/qualifier.hpp> // glm::mat
#include <glm/mat2x2.hpp> // glm::mat2x2

namespace crystal::spatial {
template<size_t kRow, size_t kCol, typename T>
using MatData = glm::mat<kRow, kCol, T>;

using Mat2fData = glm::mat2x2;
} // namespace crystal::spatial

#endif
