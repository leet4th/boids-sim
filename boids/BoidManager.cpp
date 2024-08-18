#include "BoidManager.hpp"

#include <fmt/format.h>

namespace BoidSim {

auto wrap(float val, float max_val) -> float {
    return std::fmod(val + max_val, max_val);
}

BoidManager::BoidManager(size_t in) : num_boids(in) {
    all_pos.resize(num_boids);
    all_vel.resize(num_boids);
}

auto BoidManager::init() -> void {
    for (size_t i = 0; i < num_boids; i++) {


        Eigen::Vector2f pos = Eigen::Vector2f{500, 500};

        // Eigen::Vector2f vel = Eigen::Vector2f{-1, 0};
        Eigen::Vector2f vel = Eigen::Vector2f((rand() % 100) / 100.f - 0.5f,
                                              (rand() % 100) / 100.f - 0.5f);

        vel = vel.normalized() * 200.0;

        pos.x() += 100.0 * i;
        pos.y() += 100.0 * i;

        pos.x() = wrap(pos.x(), 1280.0);
        pos.y() = wrap(pos.y(), 720.0);

        all_pos.at(i) = pos;
        all_vel.at(i) = vel;
    }
}

auto BoidManager::update(float dt_s) -> void {
    const auto all_pos_ = all_pos;
    const auto all_vel_ = all_vel;


    for (size_t i = 0; i < num_boids; i++) {
        Eigen::Vector2f& own_pos = all_pos.at(i);
        Eigen::Vector2f& own_vel = all_vel.at(i);

        // loop through other
        Eigen::Vector2f avoid_vel = Eigen::Vector2f::Zero();
        for (size_t j = 0; j < num_boids; j++) {
            if (i == j) {
                continue;
            }

            const Eigen::Vector2f& other_pos = all_pos_.at(j);
            const Eigen::Vector2f& other_vel = all_vel_.at(j);

            // avoidance
            Eigen::Vector2f dist_to_other = other_pos - own_pos;
            if (dist_to_other.norm() < 200) {
                avoid_vel -= dist_to_other;
            }
        }

        own_vel += 0.02 * avoid_vel;

        own_vel.normalize();
        own_vel *= 200;
        own_pos += own_vel * dt_s;

        // if(own_pos.x() > 1280.0 || own_pos.x() < 0.0 || own_pos.y() > 720.0 || own_pos.y() < 0.0) {
        //     fmt::print("{}: pos=[{:0.3f}, {:0.3f}]\n", i, own_pos.x(), own_pos.y());
        //     fmt::print("{}: vel=[{:0.3f}, {:0.3f}]\n", i, own_vel.x(), own_vel.y());
        // }

        own_pos.x() = wrap(own_pos.x(), 1280.0);
        own_pos.y() = wrap(own_pos.y(), 720.0);

        // fmt::print("{}: pos=[{:0.3f}, {:0.3f}]\n", i, own_pos.x(), own_pos.y());

        // if (own_pos.x() < 0) own_pos.x() = 1280;
        // if (own_pos.x() > 1280) own_pos.x() = 0;
        // if (own_pos.y() < 0) own_pos.y() = 720;
        // if (own_pos.y() > 720) own_pos.y() = 0;
    }
}

auto BoidManager::render(sf::RenderWindow& window) const -> void {
    for (size_t i = 0; i < num_boids; i++) {
        const auto& pos = all_pos.at(i);
        const auto& vel = all_vel.at(i);

        sf::ConvexShape triangle(3);
        triangle.setPoint(0, sf::Vector2f(0, 0));
        triangle.setPoint(1, sf::Vector2f(-10, 5));
        triangle.setPoint(2, sf::Vector2f(-10, -5));
        triangle.setFillColor(sf::Color::Blue);

        triangle.setPosition(pos.x(), pos.y());
        float heading_deg = atan2(vel.y(), vel.x()) * RAD2DEG;
        triangle.setRotation(heading_deg);

        window.draw(triangle);
    }
}

}  // namespace BoidSim
