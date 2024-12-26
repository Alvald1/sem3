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

int
Control::get_player_count() const {
    int player_count = 2; // Default minimum players
    auto& view = View::getInstance();

    while (true) {
        view.show_player_count_menu(player_count);
        int ch = getch();

        switch (ch) {
            case 'q':
            case 'Q':
            case 27:      // ESC key
                return 0; // Special value indicating exit
            case KEY_UP:
                if (player_count < 4) {
                    player_count++;
                }
                break;
            case KEY_DOWN:
                if (player_count > 2) {
                    player_count--;
                }
                break;
            case '\n':
            case KEY_ENTER: return player_count;
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
