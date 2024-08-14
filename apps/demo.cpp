#include <fmt/core.h>

#include <Eigen/Dense>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <cmath>
#include <vector>

#include "imgui-SFML.h"
#include "imgui.h"

#define RAD2DEG 180.0f / M_PIf

struct Boid {
    Eigen::Vector2f pos;
    Eigen::Vector2f vel;
};

std::vector<Boid> boids;

void initBoids(int count) {
    for (auto i = 0; i < count; i++) {
        Boid boid;
        boid.pos = Eigen::Vector2f(rand() % 1280, rand() % 720);
        boid.vel = Eigen::Vector2f((rand() % 100) / 100.f - 0.5f,
                                   (rand() % 100) / 100.f - 0.5f);
        boid.vel.normalize();
        boid.vel *= 100.0;
        boids.push_back(boid);
    }
}

void updateBoids(float dt_s) {
    for (auto& boid : boids) {
        boid.pos += boid.vel * dt_s;

        if (boid.pos.x() < 0) boid.pos.x() = 1280;
        if (boid.pos.x() > 1280) boid.pos.x() = 0;
        if (boid.pos.y() < 0) boid.pos.y() = 720;
        if (boid.pos.y() > 720) boid.pos.y() = 0;
    }
}

void renderBoids(sf::RenderWindow& window) {
    for (const auto& boid : boids) {
        sf::ConvexShape triangle(3);
        triangle.setPoint(0, sf::Vector2f(0, 0));
        triangle.setPoint(1, sf::Vector2f(-10, 5));
        triangle.setPoint(2, sf::Vector2f(-10, -5));
        triangle.setFillColor(sf::Color::Blue);

        triangle.setPosition(boid.pos.x(), boid.pos.y());
        float heading_deg = atan2(boid.vel.y(), boid.vel.x()) * RAD2DEG;
        triangle.setRotation(heading_deg);

        window.draw(triangle);
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Boids");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    initBoids(1000);

    float deltaTime = 0.0;
    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        deltaTime = deltaClock.getElapsedTime().asSeconds();
        float fps = 1.0 / deltaTime;
        fmt::print("fps = {:0.3f}\n", fps);

        // must create all widgets between ImGui::SFML::Update() and
        // ImGui::Render().
        ImGui::SFML::Update(window, deltaClock.restart());

        // update boids
        updateBoids(deltaTime);

        // start rendering the frame
        window.clear();

        // render boids
        renderBoids(window);

        // render a control pannel
        // ImGui::Begin("Hello, world!");
        // ImGui::Button("Look at this pretty button");
        // ImGui::End();

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}
