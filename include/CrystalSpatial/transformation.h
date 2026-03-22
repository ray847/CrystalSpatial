#ifndef CRYSTALSPATIAL_TRANSFORMATION_H_
#define CRYSTALSPATIAL_TRANSFORMATION_H_

#include <concepts>

#include <glm/detail/qualifier.hpp>

namespace crystal::spatial {

template <typename T>
concept AnyTrans = requires(const T& ct) {
  T::kComplete;
}
&&std::same_as<decltype(T::kComplete), const bool> &&
    (T::kComplete ? requires(const T& ct) { {ct(ct)}->std::same_as<T>; }
                  : requires(const T& ct) {
                      typename T::CompleteTrans;
                      {ct(ct)}->std::same_as<typename T::CompleteTrans>;
                      std::convertible_to<T, typename T::CompleteTrans>;
                    });

template <AnyTrans T>
struct CompleteTransHelper;
template <AnyTrans T> requires (T::kComplete)
struct CompleteTransHelper<T> {
  using Type = T;
};
template <AnyTrans T> requires (!T::kComplete)
struct CompleteTransHelper<T> {
  using Type = T::CompleteTrans;
};
template <AnyTrans T>
using CompleteTrans = CompleteTransHelper<T>::Type;

} // namespace crystal::spatial

#endif
