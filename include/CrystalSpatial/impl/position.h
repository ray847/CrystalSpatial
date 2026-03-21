#ifndef CRYSTALSPAIAL_IMPL_POSITION_H_
#define CRYSTALSPAIAL_IMPL_POSITION_H_

#include <glm/detail/qualifier.hpp>

namespace crystal::spatial::impl {

template <std::size_t dim, typename T>
struct Position {
  using Vec = glm::vec<dim, T>;

  std::size_t subspace;
  Vec vec;
};

} // namespace crystal::spatial::impl

#endif