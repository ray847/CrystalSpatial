cmake_minimum_required(VERSION 3.11)

if (NOT TARGET CrystalBase)
  message("Fetching CrystalBase")
  include(FetchContent)

  FetchContent_Declare(
    CrystalBase
  GIT_REPOSITORY	https://github.com/ray847/CrystalBase.git
  GIT_TAG "origin/main"
  )

  FetchContent_MakeAvailable(CrystalBase)
  message("CrystalBase Found")
endif()

