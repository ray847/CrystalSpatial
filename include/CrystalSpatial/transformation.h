#ifndef CRYSTALSPATIAL_TRANSFORMATION_H_
#define CRYSTALSPATIAL_TRANSFORMATION_H_

#include <cstddef>

#include <concepts>

#include <glm/detail/qualifier.hpp>

namespace crystal::spatial {

template <typename T>
concept AnyTrans = requires(const T& ct) {
  T::kDim;
  typename T::DType;
  {ct(ct)}->std::same_as<T>;
}
&&std::same_as<decltype(T::kDim), const std::size_t>;

} // namespace crystal::spatial

#endif
