#ifndef CRYSTALSPATIAL_TRANSFORMATION_H_
#define CRYSTALSPATIAL_TRANSFORMATION_H_

#include <cstddef>

#include "glm/detail/qualifier.hpp"

namespace crystal::spatial {

template <std::size_t dim = 3, typename T = float>
using Trans = glm::mat<dim, dim, T>;

} // namespace crystal::spatial

#endif
