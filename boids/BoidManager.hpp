#pragma once

#include <fmt/format.h>
#include <imgui-SFML.h>
#include <imgui.h>

#include <Eigen/Dense>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <cmath>
#include <vector>

#define RAD2DEG 180.0f / M_PIf

namespace BoidSim {

auto wrap(float val, float max_val) -> float;

struct BoidParams {
    float avoid_dist;
    float avoid_gain;
    float sight_dist;
    float align_gain;
    float cohesion_gain;
    bool show_avoid;
    bool show_sight;
};

class BoidManager {
   public:
    BoidManager(size_t num_boids, float world_size_x, float world_size_y);

    auto init() -> void;
    auto update(float dt_s) -> void;
    auto render(sf::RenderWindow& window) const -> void;

    auto getNumBoids() const -> size_t { return num_boids; }
    auto getAllPos() const -> const std::vector<Eigen::Vector2f>& {
        return all_pos;
    }
    auto getAllVel() const -> const std::vector<Eigen::Vector2f>& {
        return all_vel;
    }

    auto setShowAvoid(bool show_avoid) -> void;
    auto setShowSight(bool show_sight) -> void;

   private:
    size_t num_boids;
    float world_size_x;
    float world_size_y;

    std::vector<Eigen::Vector2f> all_pos;
    std::vector<Eigen::Vector2f> all_vel;
    std::vector<BoidParams> all_params;
};

}  // namespace BoidSim
