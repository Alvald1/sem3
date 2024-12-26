#include "game.hpp"

Game::Game() = default;
Game::~Game() = default;

void
Game::load() {
    try {
        parser_.parse_schools("/home/alvald1/files/sem3/oop/3/data/schools.json");
    } catch (const std::exception& e) {
        throw std::runtime_error("Failed to load schools configuration: " + std::string(e.what()));
    }
}

void
Game::start() {
    load();
    auto& view = View::getInstance();
    auto& control = Control::getInstance();
    auto& schools = Schools::getInstance();

    // Show menu and get map size
    view.show_menu();
    auto [width, height] = control.get_map_size();
    if (width == 0 && height == 0) {
        return;
    }

    // Get player count
    int player_count = control.get_player_count();
    if (player_count == 0) {
        return;
    }

    // Get available summoners
    auto summoner_abilities = schools.find_summoner_abilities();
    if (summoner_abilities.empty()) {
        throw std::runtime_error("No summoners found in the game!");
    }

    // Vector to track selected summoners
    std::vector<bool> selected(summoner_abilities.size(), false);
    std::vector<size_t> player_summoners(player_count);

    // Player selection process
    for (int i = 0; i < player_count; ++i) {
        auto selection = control.select_summoner(summoner_abilities, selected, i);
        if (!selection.has_value()) {
            return; // User cancelled
        }

        selected[selection.value()] = true;
        player_summoners[i] = summoner_abilities[selection.value()].get().get_id();
    }

    // Create and initialize map
    game_map_ = std::make_unique<Map>();
    game_map_->make_map({width, height});

    // Initialize with all passable cells
    Matrix<bool> walls(width, height, true);
    game_map_->load_from_passability_matrix(walls);

    // Create board for game display
    board_ = std::make_unique<Board>(*game_map_);

    // Main game loop
    while (control.handle_input()) {
        board_->draw();
        board_->refresh_display();
    }
}

// ...existing code...
