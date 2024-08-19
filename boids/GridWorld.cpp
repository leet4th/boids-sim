
#include "GridWorld.hpp"

namespace BoidSim {

GridWorld::GridWorld(float size_x_, float size_y_, float size_cell)
    : size_x(size_x_), size_y(size_y_) {
    nx = size_x / size_cell;
    ny = size_y / size_cell;
    n_buckets = nx * ny;
    cell_size_x = size_x / nx;
    cell_size_y = size_y / ny;
    buckets.resize(n_buckets);
};

auto GridWorld::clear() -> void {
    for (auto& bucket : buckets) {
        bucket.clear();
    }
}

auto GridWorld::add(int entity_id, const Eigen::Vector2f& pos) -> void {
    int kx = pos.x() / cell_size_x;
    int ky = pos.y() / cell_size_y;
    auto k = kx + nx * ky;
    buckets.at(k).push_back(entity_id);
}

auto GridWorld::render(sf::RenderWindow& window) const -> void {
    for (int x = 0; x < nx; x++) {
        for (int y = 0; y < ny; y++) {
            auto k = x + nx * y;
            auto count = buckets[k].size();

            // grid
            sf::Vector2f size{cell_size_x, cell_size_y};
            sf::RectangleShape square(size);
            square.setPosition(x * cell_size_x, y * cell_size_y);
            if (count > 0) {
                square.setFillColor(sf::Color(0, 255, 255, 128));
            } else {
                square.setFillColor(sf::Color::Transparent);
            }
            square.setOutlineThickness(1);
            square.setOutlineColor(sf::Color::Cyan);

            window.draw(square);
        }
    }
}

}  // namespace BoidSim