#ifndef CRYSTALSPAIAL_POSITION_H_
#define CRYSTALSPAIAL_POSITION_H_

#include <format>
#include <ostream>

#include "primitive/vec2f.h"
#include "subspace.h"

namespace crystal::spatial {
/**
 * A position in a subspace.
 * 
 * Variables:
 *  SubSpace()
 * 
 * Functions:
 *  Relative()
 *  Absolute()
 */
class Position {
 public:
  /* Constructors */
  Position(SubSpace& subspace, vec2f vec = {})
      : subspace_(subspace), vec_(vec) {}

  /* Functions */
  vec2f Relative() const { return vec_; }
  vec2f Absolute() const { return subspace_.AbsoluteTrans()(vec_); }

  /* Accessors */
  crystal::spatial::SubSpace& SubSpace() { return subspace_; }
  const crystal::spatial::SubSpace& SubSpace() const { return subspace_; }
  vec2f& Vec() { return vec_; }
  const vec2f& Vec() const { return vec_; }

 private:
  crystal::spatial::SubSpace& subspace_;
  vec2f vec_;
};
} // namespace crystal::spatial

#endif