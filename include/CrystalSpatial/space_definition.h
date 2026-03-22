#ifndef CRYSTALSPATIAL_SPACE_DEFINITION_H_
#define CRYSTALSPATIAL_SPACE_DEFINITION_H_

#include <tuple>
#include <vector>

#include "transformation.h"
#include "object.h"

namespace crystal::spatial {

template <AnyTrans Transformation, CompatibleObj<Transformation>... T>
struct SpaceDef {
  using Trans = Transformation;
  using Types = std::tuple<T...>;
  using ObjContainers = std::tuple<std::vector<ObjWrapper<T>>...>;
};

} // namespace crystal::spatial

#endif