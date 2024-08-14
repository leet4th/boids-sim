
file(GLOB src_boids "main.cpp")

add_executable(boids-sim ${src_boids})
target_link_libraries(boids-sim PRIVATE boids eigen)


file(GLOB src_demo "demo.cpp")

add_executable(demo ${src_demo})
target_link_libraries(demo PRIVATE ImGui-SFML::ImGui-SFML eigen fmt)
