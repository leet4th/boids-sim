#pragma once

#include <fmt/core.h>
#include <imgui-SFML.h>
#include <imgui.h>

#include <Eigen/Dense>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <chrono>
#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include "BoidManager.hpp"

namespace BoidSim {

struct GameConfig {
    std::string name;
    unsigned int x_range;
    unsigned int y_range;
    unsigned int frame_limit;
    size_t num_boids;
};

class Game {
   public:
    // TODO: consume in config json
    Game(const GameConfig& config);

    /// @brief Run game
    /// @return
    auto run() -> void;

   private:
    GameConfig config;
    sf::RenderWindow window;
    BoidManager manager;

    sf::Clock clock{};
    sf::Time deltaTime{};
    float fps{};

    /// @brief Init window and game state
    /// @return
    auto init() -> bool;

    /// @brief Run single frame
    /// @return
    auto step() -> void;

    /// @brief Process events
    /// @return
    auto processEvents() -> void;

    /// @brief Update game state
    /// @return
    auto update() -> void;

    /// @brief Render window
    /// @return
    auto render() -> void;

    /// @brief Shutdown window and cleanup
    /// @return
    auto shutdown() -> void;
};

}  // namespace BoidSim