#ifndef CRYSTALSPAIAL_SUBSPACE_H_
#define CRYSTALSPAIAL_SUBSPACE_H_

#include "CrystalSpatial/space_definition.h"
#include "CrystalSpatial/transformation.h"

namespace crystal::spatial::impl {
  
template <typename SpaceDef>
struct SubSpace {
  std::size_t parent;
  SpaceDef::Trans trans;
};

} // namespace crystal::spatial::impl

#endif