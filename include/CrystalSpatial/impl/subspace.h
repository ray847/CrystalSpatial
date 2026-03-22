#ifndef CRYSTALSPAIAL_SUBSPACE_H_
#define CRYSTALSPAIAL_SUBSPACE_H_

#include "CrystalSpatial/transformation.h"

namespace crystal::spatial::impl {
  
template <std::size_t dim, typename T, AnyTrans Trans>
struct SubSpace {

  std::size_t parent;
  Trans trans;
};

} // namespace crystal::spatial::impl

#endif