
#include <game.hpp>

using BoidSim::Game;
using BoidSim::GameConfig;

int main(int argc, char *argv[]) {
    Game game{GameConfig{.name = "boids",
                         .size_x = 1920,
                         .size_y = 1080,
                         .size_cell = 100,
                         .frame_limit = 60,
                         .num_boids = 100}};

    game.run();

    return 0;
}