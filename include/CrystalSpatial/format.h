#ifndef CRYSTALSPATIAL_FORMAT_H_
#define CRYSTALSPATIAL_FORMAT_H_

#include <format>
#include <string>
#include <sstream>
#include <ostream>

#include <glm/ext/matrix_common.hpp>
#include <glm/ext/vector_common.hpp>

namespace std {

template <size_t m, size_t n, typename T>
struct formatter<glm::mat<m, n, T>> : formatter<string> {
  auto format(const glm::mat<m, n, T>& mat, format_context& ctx) const {
    std::stringstream ss;
    for (std::size_t i = 0; i < m; ++i) {
      ss << "\t[" << mat[0][i];
      for (std::size_t j = 1; j < n; ++j) {
        ss << ",\t" << mat[j][i];
      }
      ss << "]\n";
    }
    return formatter<string>::format(
        std::format("mat{}x{}:\n{}", m, n, ss.str()), ctx);
  }
};

template <size_t m, typename T>
struct formatter<glm::vec<m, T>> : formatter<string> {
  auto format(const glm::vec<m, T>& vec, format_context& ctx) const {
    std::stringstream ss;
    for (std::size_t i = 0; i < m; ++i) {
      ss << "\t[" << vec[i] << "\t]\n";
    }
    return formatter<string>::format(std::format("vec{}:\n{}", m, ss.str()),
                                     ctx);
  }
};

} // namespace std

#endif