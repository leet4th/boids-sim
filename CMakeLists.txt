
cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(
    boids-sim
    VERSION 0.1
    DESCRIPTION "Boids simulation"
    LANGUAGES CXX C)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(cmake/PreventInSourceBuilds.cmake)
include(CTest)
include(FetchContent)

# fmtlib
FetchContent_Declare(
  fmtlib
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 5.3.0)
FetchContent_MakeAvailable()

# eigen
FetchContent_Declare(
    eigen
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
    GIT_TAG tags/3.4.0
    GIT_SHALLOW TRUE
)

# googletest
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.15.2
)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

# make availible
FetchContent_MakeAvailable(eigen fmtlib)

add_subdirectory(apps)
add_subdirectory(boids)
# add_subdirectory(tests)
