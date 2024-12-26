#include "control.hpp"
#include <ncurses.h>
#include <sstream>

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
    int width = 10, height = 10;
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
    // TODO: Implement actual UI interaction to get action
    return SummonerAction::ACCUMULATE_ENERGY; // Default return for now
}

[[nodiscard]] size_t
Control::get_ability_choice() const {
    return 1; // Default return for now
}

[[nodiscard]] Position
Control::get_position_choice() const {
    return Position(0, 0); // Default return for now
}

[[nodiscard]] Control::TroopAction
Control::get_troop_action() const {
    // TODO: Implement actual UI interaction
    return TroopAction::SKIP_TURN; // Default return for now
}
