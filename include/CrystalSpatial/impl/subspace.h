#ifndef CRYSTALSPAIAL_SUBSPACE_H_
#define CRYSTALSPAIAL_SUBSPACE_H_

#include <cstddef>

namespace crystal::spatial::impl {
  
template <typename SpaceDef>
struct SubSpace {
  std::size_t parent;
  SpaceDef::Trans trans;
};

} // namespace crystal::spatial::impl

#endif