#ifndef CRYSTALSPATIAL_OBJECT_H_
#define CRYSTALSPATIAL_OBJECT_H_

#include <concepts>
#include <utility>
#include "transformation.h"

namespace crystal::spatial {

template <typename T>
concept AnyObj = true;

template <typename Obj, typename Trans>
concept CompatibleObj = requires(const Trans& t, const Obj& obj) {
  t(obj);
}
&&AnyTrans<Trans>&& AnyObj<Obj>;

template <AnyObj Obj>
class ObjWrapper {
 public:
  std::size_t parent_;
  Obj obj_;
  /* Constructor */
  template <typename... Args>
  ObjWrapper(std::size_t parent, Args&&... args)
      : parent_(parent), obj_(std::forward<Args>(args)...) {}
};

} // namespace crystal::spatial
#endif