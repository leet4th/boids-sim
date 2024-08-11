
file(GLOB SRC "*.cpp" "*.hpp")

add_library(boids ${SRC})

target_link_libraries(boids PRIVATE fmt::fmt)

target_include_directories(boids INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})