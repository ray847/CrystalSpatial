cmake_minimum_required(VERSION 3.15)

# Project Options
project(CrystalSpatial CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# External Libraries
add_subdirectory(lib/glm)
add_subdirectory(lib/CrystalBase)

# Internal Library
add_library(CrystalSpatial)
target_sources(CrystalSpatial
  PRIVATE
    src/spatial.cpp
    src/format.cpp
)
target_include_directories(CrystalSpatial
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(CrystalSpatial
  PUBLIC
    glm::glm
    CrystalBase
)

if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  message(STATUS "Building CrystalSpatial Standalone (with tests/main)")
  # Main
  add_executable(main main.cpp)
  target_include_directories(main
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
  )
  target_link_libraries(main
  PRIVATE
    CrystalSpatial
  )
  # Testing
  add_subdirectory(test)
endif()

