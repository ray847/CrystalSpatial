#ifndef CRYSTALSPAIAL_SUBSPACE_H_
#define CRYSTALSPAIAL_SUBSPACE_H_

#include "CrystalSpatial/transformation.h"

namespace crystal::spatial::impl {
  
template <std::size_t dim, typename T>
struct SubSpace {
  using Transformation = Trans<dim, T>;

  std::size_t parent;
  Transformation trans;
};

} // namespace crystal::spatial::impl

#endif