
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

include(cmake/Dependencies.cmake)
add_subdirectory(apps)
add_subdirectory(boids)
# add_subdirectory(tests)
