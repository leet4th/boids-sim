
file(GLOB SRC "main.cpp")

add_executable(boids-sim ${SRC})

target_link_libraries(boids-sim PRIVATE greeter)
