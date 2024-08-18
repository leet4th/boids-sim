
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
# set_property(GLOBAL CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

include(cmake/PreventInSourceBuilds.cmake)
include(CTest)

# ccache
find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    message(STATUS "Using ccache")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
else()
    message(STATUS "WARNING ccache not found")
endif()

# # valgrind
# find_program(CTEST_MEMORYCHECK_COMMAND NAMES valgrind)

include(cmake/Dependencies.cmake)
add_subdirectory(apps)
add_subdirectory(boids)
# add_subdirectory(tests)
