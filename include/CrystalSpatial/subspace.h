#ifndef CRYSTALSPATIAL_SUBSPACE_H_
#define CRYSTALSPATIAL_SUBSPACE_H_

#include <vector> // std::vector
#include <memory_resource> // std::pmr

#include <CrystalBase/stable_vector.h> // StableVector

#include "CrystalSpatial/vector.h" // Vec
#include "CrystalSpatial/transformation.h" // Trans
#include "CrystalSpatial/index.h" // SpatialIdx

namespace crystal::spatial {

/* Class Declaration (for friend) */
class Space;

class SubSpace {
public:
  friend Space;
  using allocator_type = std::pmr::polymorphic_allocator<>;
  /* Constructor */
  SubSpace() : SubSpace(allocator_type{}) {}
  explicit SubSpace(const allocator_type& allocator):
    children_(allocator),
    trans_(),
    vecs_(allocator) {}
  SubSpace(const Trans& trans, const allocator_type& allocator = {}):
    children_(allocator),
    trans_(trans),
    vecs_(allocator) {}
  SubSpace(const SubSpace& other, const allocator_type& allocator = {}):
    children_(other.children_, allocator),
    vecs_(other.vecs_, allocator) {}
  SubSpace(SubSpace&& other, const allocator_type& allocator = {}):
    children_(std::move(other.children_), allocator),
    vecs_(std::move(other.vecs_), allocator) {}
  /* Assignment Operator */
  SubSpace& operator=(const SubSpace& rhs) = default;
  SubSpace& operator=(SubSpace&& rhs) = default;
  /* Destructor */
  ~SubSpace() = default;
  /* Functions */
  allocator_type get_allocator() const {return children_.get_allocator();}
  template<typename...Args>
  VecIdx CreateVec(Args... args) {
    return vecs_.Emplace(args...);
  }
  void DeleteVec(VecIdx vec_idx) {
    vecs_.Erase(vec_idx);
  }
private:
  /* Variables */
  SubSpaceIdx parent_;
  std::pmr::vector<SubSpaceIdx> children_;
  Trans trans_;
  pmr::StableVector<Vec> vecs_;
};
} // namespace crystal::spatial

#endif
