#pragma once

#include <fmt/format.h>
#include <imgui-SFML.h>
#include <imgui.h>

#include <Eigen/Dense>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <cmath>
#include <list>
#include <vector>

namespace BoidSim {

class GridWorld {
   public:
    GridWorld(float size_x, float size_y, float size_cell);
    auto render(sf::RenderWindow& window) const -> void;

    auto getNumX() const -> int { return nx; }
    auto getNumY() const -> int { return ny; }
    auto getCellSizeX() const -> float { return cell_size_x; }
    auto getCellSizeY() const -> float { return cell_size_y; }
    auto getWorldSizeX() const -> float { return size_x; }
    auto getWorldSizeY() const -> float { return size_y; }

    auto clear() -> void;
    auto add(int entity_id, const Eigen::Vector2f& pos) -> void;

   private:
    float size_x;
    float size_y;
    int nx;
    int ny;
    int n_buckets;
    float cell_size_x;
    float cell_size_y;

    std::vector<std::list<int>> buckets{};
};

}  // namespace BoidSim