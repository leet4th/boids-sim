#include "BoidManager.hpp"

namespace BoidSim {

auto wrap(float val, float max_val) -> float {
    return std::fmod(val + max_val, max_val);
}

BoidManager::BoidManager(size_t num_boids_, float world_size_x_,
                         float world_size_y_)
    : num_boids(num_boids_),
      world_size_x(world_size_x_),
      world_size_y(world_size_y_) {
    all_pos.resize(num_boids);
    all_vel.resize(num_boids);
    all_params.resize(num_boids);
}

auto BoidManager::init() -> void {
    for (size_t i = 0; i < num_boids; i++) {
        // position
        Eigen::Vector2f pos = Eigen::Vector2f{500, 500};
        pos.x() += 100.0 * i;
        pos.y() += 100.0 * i;
        pos.x() = wrap(pos.x(), world_size_x);
        pos.y() = wrap(pos.y(), world_size_y);

        // velocity
        auto speed = 200.0f;
        auto heading = std::fmod(rand(), 2 * M_PI) - M_PI;
        Eigen::Vector2f vel =
            Eigen::Vector2f{std::sin(heading), std::cos(heading)} * speed;

        all_pos[i] = pos;
        all_vel[i] = vel;
        all_params[i] = BoidParams{.avoid_dist = 50.0,
                                   .avoid_gain = 1000.0,
                                   .sight_dist = 300.0,
                                   .align_gain = 0.5,
                                   .cohesion_gain = 1.4,
                                   .show_avoid = false,
                                   .show_sight = false};
    }
}

auto BoidManager::update(float dt_s) -> void {
    const auto all_pos_ = all_pos;
    const auto all_vel_ = all_vel;

    for (size_t i = 0; i < num_boids; i++) {
        Eigen::Vector2f& own_pos = all_pos[i];
        Eigen::Vector2f& own_vel = all_vel[i];
        const auto& own_params = all_params[i];

        // loop through other
        Eigen::Vector2f avg_pos = own_pos;
        Eigen::Vector2f avg_vel = own_vel;
        Eigen::Vector2f avoid_vel = Eigen::Vector2f::Zero();
        size_t neighbor_count = 1;
        for (size_t j = 0; j < num_boids; j++) {
            if (i == j) {
                continue;
            }

            const Eigen::Vector2f& other_pos = all_pos_[j];
            const Eigen::Vector2f& other_vel = all_vel_[j];

            // distance to neighbor
            // Eigen::Vector2f dist_to_other = other_pos - own_pos;
            // float width = 1280.0;
            // if(std::abs(dist_to_other.x()) > width/2.0) {
            //     dist_to_other.x() = other_pos.x() + width -own_pos.x();
            // }

            // float height = 720.0;
            // if(std::abs(dist_to_other.y()) > height/2.0) {
            //     auto shift = std::signbit(dist_to_other.y()) ? -height :
            //     height; dist_to_other.y() = other_pos.y() + shift -
            //     own_pos.y();
            // }

            Eigen::Vector2f dist_to_other = other_pos - own_pos;
            auto dist_mag_sq = dist_to_other.squaredNorm();

            // avoidance
            if (dist_mag_sq < own_params.avoid_dist * own_params.avoid_dist &&
                dist_mag_sq > 0.0f) {
                avoid_vel -= dist_to_other / (dist_mag_sq);
            }

            // accumulate
            if (dist_mag_sq < own_params.sight_dist * own_params.sight_dist) {
                neighbor_count += 1;
                avg_pos += other_pos;
                avg_vel += other_vel;
            }
        }

        // average across neighbors
        avg_pos /= neighbor_count;
        avg_vel /= neighbor_count;

        Eigen::Vector2f dist_to_avg_pos = avg_pos - own_pos;

        own_vel += own_params.avoid_gain * avoid_vel +
                   own_params.align_gain * avg_vel +
                   own_params.cohesion_gain * dist_to_avg_pos;

        own_vel.normalize();
        own_vel *= 200.0f;

        own_pos += own_vel * dt_s;

        own_pos.x() = wrap(own_pos.x(), world_size_x);
        own_pos.y() = wrap(own_pos.y(), world_size_y);
    }
}

auto BoidManager::render(sf::RenderWindow& window) const -> void {
    for (size_t i = 0; i < num_boids; i++) {
        const auto& pos = all_pos[i];
        const auto& vel = all_vel[i];
        const auto& params = all_params[i];

        // draw body
        sf::ConvexShape body(3);
        float length = 20.0f;
        float half_width = 8.0f;
        auto cy = length / 3.0f;
        body.setPoint(0, sf::Vector2f(length, 0));
        body.setPoint(1, sf::Vector2f(0, half_width));
        body.setPoint(2, sf::Vector2f(0, -half_width));
        body.setOrigin(cy, 0.0);
        body.setFillColor(sf::Color::Blue);
        body.setOutlineColor(sf::Color::Black);
        body.setOutlineThickness(1.0);

        body.setPosition(pos.x(), pos.y());
        float heading_deg = atan2(vel.y(), vel.x()) * RAD2DEG;
        body.setRotation(heading_deg);

        window.draw(body);

        // draw avoidance distance
        if (params.show_avoid) {
            sf::CircleShape avoid_circle(params.avoid_dist);
            avoid_circle.setOrigin(params.avoid_dist, params.avoid_dist);
            avoid_circle.setPosition(pos.x(), pos.y());
            avoid_circle.setFillColor(sf::Color::Transparent);
            avoid_circle.setOutlineThickness(2);
            avoid_circle.setOutlineColor(sf::Color::Red);

            window.draw(avoid_circle);
        }

        // draw sight distance
        if (params.show_sight) {
            sf::CircleShape sight_circle(params.sight_dist);
            sight_circle.setOrigin(params.sight_dist, params.sight_dist);
            sight_circle.setPosition(pos.x(), pos.y());
            sight_circle.setFillColor(sf::Color::Transparent);
            sight_circle.setOutlineThickness(2);
            sight_circle.setOutlineColor(sf::Color::Green);
            window.draw(sight_circle);
        }
    }
}

auto BoidManager::setShowAvoid(bool show_avoid) -> void {
    for (auto& param : all_params) {
        param.show_avoid = show_avoid;
    }
}

auto BoidManager::setShowSight(bool show_sight) -> void {
    for (auto& param : all_params) {
        param.show_sight = show_sight;
    }
}

}  // namespace BoidSim
