
#include <game.hpp>

using BoidSim::Game;
using BoidSim::GameConfig;

int main(int argc, char *argv[]) {
    Game game{GameConfig{.name = "boids",
                         .x_range = 1280,
                         .y_range = 720,
                         .frame_limit = 60,
                         .num_boids = 70}};

    game.run();

    return 0;
}