#include "game.hpp"

#include "managers/entity_manager.hpp"
#include "managers/map_manager.hpp"
#include "queue/entity/builder/entity_director.hpp"

Game::Game() = default;

Game::~Game() {
    // Let View handle the cleanup
    View::getInstance().cleanup();
}

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
    auto& entity_manager = EntityManager::getInstance();
    auto& map_manager = MapManager::getInstance();

    // Show menu and get map size
    view.show_menu();
    auto [width, height] = control.get_map_size();
    if (width == 0 && height == 0) {
        return;
    }

    // Get available summoners
    auto summoner_abilities = schools.find_summoner_abilities();
    if (summoner_abilities.empty()) {
        throw std::runtime_error("No summoners found in the game!");
    }

    // Vector to track selected summoners
    const int player_count = 2; // Fixed number of players
    std::vector<bool> selected(summoner_abilities.size(), false);
    std::vector<const Ability*> player_summoners;
    player_summoners.reserve(player_count);

    // Player selection process
    for (int i = 0; i < player_count; ++i) {
        auto selection = control.select_summoner(summoner_abilities, selected, i);
        if (!selection.has_value()) {
            return; // User cancelled
        }

        selected[selection.value()] = true;
        player_summoners.push_back(&summoner_abilities[selection.value()].get());
    }

    // Create and initialize map
    map_manager.make_map({width, height});
    Matrix<bool> walls(width, height, true);
    map_manager.load_from_passability_matrix(walls);

    // Create fixed positions for 2 players
    std::vector<Position> summoner_positions = {
        Position(0, height - 1), // Player 1: bottom-left
        Position(width - 1, 0)   // Player 2: top-right
    };

    // Create and place summoners
    for (int i = 0; i < player_count; ++i) {
        const Ability& ability = *player_summoners[i];

        // Verify position is within map bounds
        Position pos = summoner_positions[i];
        if (pos.get_x() >= width || pos.get_y() >= height) {
            throw std::runtime_error("Invalid summoner position: (" + std::to_string(pos.get_x()) + ","
                                     + std::to_string(pos.get_y()) + ")");
        }

        // Create summoner
        auto summoner = std::make_unique<Summoner>(
            EntityDirector::createSummoner(ability, ability.get_energy(), ability.get_creature().get_damage()));

        // Add to entity manager first
        size_t summoner_id = summoner->get_id();
        entity_manager.add_entity(std::move(summoner));

        // Then try to add to map
        if (!map_manager.add_entity(summoner_id, pos)) {
            throw std::runtime_error("Failed to place summoner at position: (" + std::to_string(pos.get_x()) + ","
                                     + std::to_string(pos.get_y()) + ")");
        }
    }

    // Create board for game display
    board_ = std::make_unique<Board>(map_manager);

    // Main game loop
    int ch;
    while ((ch = getch()) != 'q') {
        switch (ch) {
            case KEY_UP: board_->scroll_up(); break;
            case KEY_DOWN: board_->scroll_down(); break;
            case KEY_LEFT: board_->scroll_left(); break;
            case KEY_RIGHT: board_->scroll_right(); break;
        }
        board_->draw();
        board_->refresh_display();
    }
}

// ...existing code...
