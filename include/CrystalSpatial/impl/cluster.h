#ifndef CRYSTALSPATIAL_IMPL_CLUSTER_H_
#define CRYSTALSPATIAL_IMPL_CLUSTER_H_

#include <vector>

#include <glm/detail/qualifier.hpp>

namespace crystal::spatial::impl {

template <std::size_t kDim, typename T>
struct Cluster {
  using Vec = glm::vec<kDim, T>;

  std::size_t subspace;
  std::vector<Vec> vecs;
};

}

#endif