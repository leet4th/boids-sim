#include "game.hpp"

namespace BoidSim {

Game::Game(const GameConfig& in)
    : config(in),
      window(sf::VideoMode(config.x_range, config.y_range), config.name.data()),
      manager(config.num_boids) {
    // window.setFramerateLimit(config.frame_limit);
    window.setVerticalSyncEnabled(true);
}

auto Game::run() -> void {
    if (init() == false) {
        fmt::print("Game failed to init\n");
    }

    clock.restart();
    while (window.isOpen()) {
        deltaTime = clock.restart();

        int n = 60 ;
        float  alpha = 2.0f / (n + 1);
        fps = alpha * 1000000 / deltaTime.asMicroseconds() + (1.0f-alpha)* fps;
        step();
    }

    shutdown();
}

auto Game::init() -> bool {
    manager.init();
    return ImGui::SFML::Init(window);
}

auto Game::step() -> void {
    processEvents();
    update();
    render();
}

auto Game::processEvents() -> void {
    // process events
    sf::Event event;
    while (window.pollEvent(event)) {
        ImGui::SFML::ProcessEvent(event);

        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

auto Game::update() -> void { manager.update(deltaTime.asSeconds()); }

auto Game::render() -> void {
    // render window
    // must create all widgets between ImGui::SFML::Update() and
    // ImGui::Render()
    ImGui::SFML::Update(window, clock.restart());
    window.clear();

    manager.render(window);

    ImGui::Begin("Configuration");
    ImGui::SeparatorText("Parameters");
    ImGui::Text("Number of boids: %s",
                std::to_string(config.num_boids).c_str());
    ImGui::SeparatorText("Diagnostics");
    ImGui::Text("FPS: %s", std::to_string(fps).c_str());
    ImGui::End();

    // ImGui::ShowDemoWindow();

    ImGui::SFML::Render(window);
    window.display();
}

auto Game::shutdown() -> void { ImGui::SFML::Shutdown(); }

}  // namespace BoidSim
