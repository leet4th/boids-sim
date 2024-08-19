#include "game.hpp"

namespace BoidSim {

Game::Game(const GameConfig& in)
    : config(in),
      window(sf::VideoMode(config.size_x, config.size_y), config.name.data()),
      manager(config.num_boids, static_cast<float>(config.size_x),
              static_cast<float>(config.size_y)),
      grid_world(static_cast<float>(config.size_x),
                 static_cast<float>(config.size_y), config.size_cell) {
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

        int n = 60;
        float alpha = 2.0f / (n + 1);
        fps =
            alpha * 1000000 / deltaTime.asMicroseconds() + (1.0f - alpha) * fps;
        step();
    }

    shutdown();
}

auto Game::init() -> bool {
    reset();
    return ImGui::SFML::Init(window);
}

auto Game::reset() -> void { manager.init(); }

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

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Space) {
                is_paused = !is_paused;
            }
            if (event.key.code == sf::Keyboard::R) {
                reset();
            }
        }
    }
}

auto Game::update() -> void {
    grid_world.clear();
    const auto& all_pos = manager.getAllPos();
    for (int i = 0; i < manager.getNumBoids(); i++) {
        grid_world.add(i, all_pos[i]);
    }

    if (!is_paused || do_step) {
        manager.update(deltaTime.asSeconds());
        do_step = false;
    }
}

auto Game::render() -> void {
    // render window
    // must create all widgets between ImGui::SFML::Update() and
    // ImGui::Render()
    ImGui::SFML::Update(window, clock.restart());
    window.clear();

    grid_world.render(window);
    manager.render(window);

    ImGui::Begin("Control Panel");

    if (ImGui::Button("Reset")) {
        reset();
    }

    if (ImGui::Button("Step")) {
        do_step = true;
    }

    if (ImGui::Button(is_paused ? "Resume" : "Pause")) {
        is_paused = !is_paused;
    }

    if (ImGui::Button(show_avoid ? "Hide Avoid Distance"
                                 : "Show Avoid Distance")) {
        show_avoid = !show_avoid;
        manager.setShowAvoid(show_avoid);
    }

    if (ImGui::Button(show_sight ? "Hide Sight Distance"
                                 : "Show Sight Distance")) {
        show_sight = !show_sight;
        manager.setShowSight(show_sight);
    }
    ImGui::Text("\n");

    ImGui::SeparatorText("Parameters - boids");
    ImGui::Text("Number of boids: %zu", manager.getNumBoids());
    ImGui::Text("\n");

    ImGui::SeparatorText("Parameters - grid");
    ImGui::Text("Size: (%d x %d)", grid_world.getNumX(), grid_world.getNumY());
    ImGui::Text("Cell Size: (%.1f x %.1f)", grid_world.getCellSizeX(),
                grid_world.getCellSizeY());
    ImGui::Text("\n");

    ImGui::SeparatorText("Diagnostics");
    ImGui::Text("FPS: %d", fps);
    ImGui::End();

    // ImGui::ShowDemoWindow();

    ImGui::SFML::Render(window);
    window.display();
}

auto Game::shutdown() -> void { ImGui::SFML::Shutdown(); }

}  // namespace BoidSim
