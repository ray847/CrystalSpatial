#ifndef CRYSTALSPAIAL_SUBSPACE_H_
#define CRYSTALSPAIAL_SUBSPACE_H_

#include "primitive/transformation.h"
#include "primitive/vec2f.h"
#include "primitive/constants.h"

namespace crystal::spatial {
/**
 * A subspace that can apply a affine transformation to its contents.
 * 
 * Variable:
 *  Trans() The affine transformation in the forms of a 3x3 matrix.
 *  Parent() A pointer to the parent subspace.
 *  This can be set to `nullptr` to indicate a root subspace.
 *
 * Function:
 *  RelativeTrans()
 *  AbsoluteTrans()
 *  RelativeOrigin()
 *  AbsoluteOrigin()
 */
class SubSpace {
 public:
  /* Constructor */
  SubSpace(SubSpace* parent = nullptr, const trans& trans = identity<mat3f>())
      : trans_(trans), parent_(parent) {}
  /* Functions */
  trans RelativeTrans() const { return trans_; }
  trans AbsoluteTrans() const {
    return (parent_ == nullptr) ? trans_ : parent_->trans_(Trans());
  }
  vec2f RelativeOrigin() const { return Trans()(vec2f{0.0f, 0.0f}); }
  vec2f AbsoluteOrigin() const { return AbsoluteTrans()(vec2f{0.0f, 0.0f}); }

  /* Accessors */
  trans& Trans() { return trans_; }
  trans Trans() const { return trans_; }
  SubSpace*& Parent() { return parent_; }
  SubSpace* Parent() const { return parent_; }

 private:
  trans trans_;
  SubSpace* parent_;
};


} // namespace crystal::spatial

#endif