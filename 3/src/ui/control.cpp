#include "control.hpp"
#include <ncurses.h>
#include <sstream>

#include "board.hpp"
#include "managers/entity_manager.hpp"
#include "managers/map_manager.hpp"
#include "queue/entity/summoner.hpp"
#include "view.hpp"

Control* Control::instance = nullptr;

Control&
Control::getInstance() {
    if (instance == nullptr) {
        instance = new Control();
    }
    return *instance;
}

std::pair<int, int>
Control::get_map_size() const {
    int width = 6, height = 6;
    bool width_selected = true;
    auto& view = View::getInstance();

    while (true) {
        view.show_form(width, height, width_selected);
        int ch = getch();

        switch (ch) {
            case 'q':
            case 'Q':
            case 27:           // ESC key
                return {0, 0}; // Special value indicating exit
            case KEY_LEFT:
            case KEY_RIGHT: width_selected = !width_selected; break;
            case KEY_UP:
                if (width_selected) {
                    width = std::min(width + 1, 50);
                } else {
                    height = std::min(height + 1, 50);
                }
                break;
            case KEY_DOWN:
                if (width_selected) {
                    width = std::max(width - 1, 5);
                } else {
                    height = std::max(height - 1, 5);
                }
                break;
            case '\n':
            case KEY_ENTER: return {width, height};
        }
    }
}

bool
Control::handle_input() {
    int ch = getch();
    if (ch == 'q' || ch == 'Q') {
        return false;
    }
    return true;
}

void
Control::handleInput() {
    // Implement input handling
}

void
Control::update() {
    // Implement update logic
}

[[nodiscard]] Control::SummonerAction
Control::get_summoner_action() const {
    auto& board = Board::getInstance(MapManager::getInstance());
    while (true) {
        int ch = getch();
        switch (ch) {
            case KEY_UP: board.scroll_up(); break;
            case KEY_DOWN: board.scroll_down(); break;
            case KEY_LEFT: board.scroll_left(); break;
            case KEY_RIGHT: board.scroll_right(); break;
            case '1': return SummonerAction::SUMMON_TROOP;
            case '2': return SummonerAction::ACCUMULATE_ENERGY;
            case '3': return SummonerAction::UPGRADE_SCHOOL;
            case '4': return SummonerAction::SKIP_TURN;
            default: continue; // Игнорируем другие клавиши
        }
        board.draw();
        board.refresh_display();
    }
}

[[nodiscard]] size_t
Control::get_ability_choice(const std::vector<std::reference_wrapper<const Ability>>& abilities, size_t current_energy,
                            size_t current_experience) {
    auto& view = View::getInstance();
    auto& board = Board::getInstance(MapManager::getInstance());
    current_ability_selection = 0;

    if (abilities.empty()) {
        return SIZE_MAX;
    }

    while (true) {
        view.send_abilities(current_energy, current_experience, abilities, View::AbilityDisplayType::AVAILABLE,
                            current_ability_selection);

        int ch = getch();
        switch (ch) {
            case KEY_UP: board.scroll_up(); break;
            case KEY_DOWN: board.scroll_down(); break;
            case KEY_LEFT: board.scroll_left(); break;
            case KEY_RIGHT: board.scroll_right(); break;
            case '\t': // Use Tab to navigate abilities instead
                if (current_ability_selection < abilities.size() - 1) {
                    current_ability_selection++;
                } else {
                    current_ability_selection = 0;
                }
                break;
            case KEY_BTAB: // Shift+Tab for reverse navigation
                if (current_ability_selection > 0) {
                    current_ability_selection--;
                } else {
                    current_ability_selection = abilities.size() - 1;
                }
                break;
            case '\n':
            case KEY_ENTER:
                if (abilities[current_ability_selection].get().get_energy() <= current_energy) {
                    view.clear_ability_panel(); // Add this line
                    return abilities[current_ability_selection].get().get_id();
                }
                break;
            case 27:                        // ESC
                view.clear_ability_panel(); // Add this line
                return SIZE_MAX;
        }
        board.draw();
        board.refresh_display();
    }
}

[[nodiscard]] Position
Control::get_position_choice(Position current_pos) const {
    auto& map_manager = MapManager::getInstance();
    auto& board = Board::getInstance(map_manager);
    Position cursor_pos = current_pos;
    auto [height, width] = map_manager.get_size();

    while (true) {
        board.highlight_cell(cursor_pos);
        board.draw();
        board.refresh_display();

        int ch = getch();
        Position new_pos = cursor_pos;

        switch (ch) {
            case KEY_UP: board.scroll_up(); break;
            case KEY_DOWN: board.scroll_down(); break;
            case KEY_LEFT: board.scroll_left(); break;
            case KEY_RIGHT: board.scroll_right(); break;
            case 'w':
            case 'W':
                if (cursor_pos.get_y() > 0) {
                    new_pos = Position(cursor_pos.get_y() - 1, cursor_pos.get_x());
                }
                break;
            case 's':
            case 'S':
                if (cursor_pos.get_y() < height - 1) {
                    new_pos = Position(cursor_pos.get_y() + 1, cursor_pos.get_x());
                }
                break;
            case 'a':
            case 'A':
                if (cursor_pos.get_x() > 0) {
                    new_pos = Position(cursor_pos.get_y(), cursor_pos.get_x() - 1);
                }
                break;
            case 'd':
            case 'D':
                if (cursor_pos.get_x() < width - 1) {
                    new_pos = Position(cursor_pos.get_y(), cursor_pos.get_x() + 1);
                }
                break;
            case '\n':
            case KEY_ENTER: board.clear_highlight(); return cursor_pos;
            case 27: // ESC
                return Position(0, 0);
        }

        cursor_pos = new_pos;
        board.draw();
        board.refresh_display();
    }
}

[[nodiscard]] Control::TroopAction
Control::get_troop_action() const {
    auto& board = Board::getInstance(MapManager::getInstance());
    while (true) {
        int ch = getch();
        switch (ch) {
            case KEY_UP: board.scroll_up(); break;
            case KEY_DOWN: board.scroll_down(); break;
            case KEY_LEFT: board.scroll_left(); break;
            case KEY_RIGHT: board.scroll_right(); break;
            case '1': return TroopAction::MOVE;
            case '2': return TroopAction::EFFECT;
            case '3': return TroopAction::ATTACK;
            case '4': return TroopAction::SKIP_TURN;
            default: continue; // Игнорируем другие клавиши
        }
        board.draw();
        board.refresh_display();
    }
}

std::optional<size_t>
Control::select_summoner(const std::vector<std::reference_wrapper<const Ability>>& summoners,
                         const std::vector<bool>& selected, int current_player) const {
    auto& view = View::getInstance();
    int current_selection = 0;

    while (true) {
        view.show_summoners_selection(summoners, selected, current_player, current_selection);
        int ch = getch();

        switch (ch) {
            case KEY_UP:
                if (current_selection > 0) {
                    current_selection--;
                }
                break;
            case KEY_DOWN:
                if (current_selection < static_cast<int>(summoners.size() - 1)) {
                    current_selection++;
                }
                break;
            case '\n':
            case KEY_ENTER:
                if (!selected[current_selection]) {
                    return current_selection;
                }
                break;
            case 27: // ESC
                return std::nullopt;
        }
    }
}
