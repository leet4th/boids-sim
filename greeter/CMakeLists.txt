
file(GLOB SRC "*.cpp" "*.hpp")

add_library(greeter ${SRC})

target_link_libraries(greeter PRIVATE fmt::fmt)

target_include_directories(greeter INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})