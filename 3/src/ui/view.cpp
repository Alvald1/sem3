#include "view.hpp"
#include <string>

View* View::instance = nullptr;

View&
View::getInstance() {
    if (instance == nullptr) {
        instance = new View();
    }
    return *instance;
}

View::View() { init(); }

View::~View() { cleanup(); }

void
View::init() {
    window = initscr();
    noecho();
    cbreak();
    keypad(window, TRUE);
    curs_set(0);
    start_color();
    init_colors();
}

void
View::init_colors() {
    init_pair(1, COLOR_WHITE, COLOR_BLACK); // Default/Menu
}

void
View::show_menu() const {
    clear_screen();
    int y = LINES / 2 - 2;
    mvprintw(y, COLS / 2 - 12, "Welcome to the Game!");
    mvprintw(y + 2, COLS / 2 - 20, "Use arrows to navigate, Enter to confirm");
    refresh_display();
}

void
View::show_form(int width, int height, bool width_selected) const {
    clear_screen();
    draw_input_form(width, height, width_selected);
    refresh_display();
}

void
View::draw_input_form(int width, int height, bool width_selected) const {
    int center_y = LINES / 2;
    int center_x = COLS / 2;

    // Draw form boxes
    mvprintw(center_y - 4, center_x - 20, "Map Size Configuration");

    // Width input box
    attron(COLOR_PAIR(1));
    mvprintw(center_y - 2, center_x - 15, "Width: ");
    if (width_selected) {
        attron(A_REVERSE);
    }
    mvprintw(center_y - 2, center_x - 8, "[%3d]", width);
    if (width_selected) {
        attroff(A_REVERSE);
    }

    // Height input box
    mvprintw(center_y, center_x - 15, "Height:");
    if (!width_selected) {
        attron(A_REVERSE);
    }
    mvprintw(center_y, center_x - 8, "[%3d]", height);
    if (!width_selected) {
        attroff(A_REVERSE);
    }

    // Updated instructions with exit option
    mvprintw(center_y + 3, center_x - 35, "(Left/Right) switch | (Up/Down) change | Enter confirm | Q/Esc exit");
    attroff(COLOR_PAIR(1));
}

void
View::clear_screen() const {
    clear();
}

void
View::refresh_display() const {
    refresh();
}

void
View::cleanup() {
    clear();             // Clear the screen
    refresh();           // Refresh to show the clear screen
    curs_set(1);         // Show cursor
    echo();              // Enable echo
    nocbreak();          // Disable cbreak mode
    endwin();            // End curses mode
    printf("\033[?25h"); // Show cursor (ANSI escape sequence)
}

const char*
View::get_title(AbilityDisplayType type) const {
    switch (type) {
        case AbilityDisplayType::AVAILABLE: return "Available Abilities:";
        case AbilityDisplayType::UPGRADABLE: return "Upgradable Abilities:";
        default: return "Unknown Ability Type";
    }
}

const char*
View::get_empty_message(AbilityDisplayType type) const {
    switch (type) {
        case AbilityDisplayType::AVAILABLE: return "No abilities available";
        case AbilityDisplayType::UPGRADABLE: return "No abilities to upgrade";
        default: return "No abilities";
    }
}

void
View::send_abilities(const std::vector<std::reference_wrapper<const Ability>>& abilities,
                     AbilityDisplayType type) const {
    clear_screen();
    mvprintw(0, 0, "%s", get_title(type));

    if (abilities.empty()) {
        mvprintw(2, 0, "%s", get_empty_message(type));
    } else {
        int y = 2;
        for (const auto& ability : abilities) {
            const auto& icon = get_ability_icon(ability.get().get_id());
            mvprintw(y++, 2, "- %s %s", ability.get().get_name().c_str(), icon.c_str());
        }
    }
    refresh_display();
}

void
View::add_ability_icon(size_t ability_id, std::string icon) {
    ability_icons[ability_id] = std::move(icon);
}

const std::string&
View::get_ability_icon(size_t ability_id) const {
    static const std::string empty_icon = "?";
    auto it = ability_icons.find(ability_id);
    return it != ability_icons.end() ? it->second : empty_icon;
}

bool
View::has_ability_icon(size_t ability_id) const {
    return ability_icons.find(ability_id) != ability_icons.end();
}

void
View::show_player_count_menu(int current_count) const {
    clear_screen();
    int center_y = LINES / 2;
    int center_x = COLS / 2;

    mvprintw(center_y - 4, center_x - 15, "Select number of players");
    attron(A_REVERSE);
    mvprintw(center_y - 2, center_x - 5, "[ %d ]", current_count);
    attroff(A_REVERSE);
    mvprintw(center_y + 2, center_x - 25, "Use Up/Down to change, Enter to confirm");
    refresh_display();
}

void
View::show_summoners_selection(const std::vector<std::reference_wrapper<const Ability>>& summoners,
                               const std::vector<bool>& selected, int current_player, int current_selection) const {
    clear_screen();

    mvprintw(1, COLS / 2 - 15, "Player %d: Choose your summoner", current_player + 1);
    mvprintw(3, 2, "Use UP/DOWN to navigate, ENTER to select, ESC to exit");

    int start_y = 5;
    int start_x = 2;
    int box_width = 40;
    int box_height = 6; // Reduced height since we're showing fewer fields
    int cols = COLS / (box_width + 2);

    for (size_t i = 0; i < summoners.size(); ++i) {
        const auto& ability = summoners[i].get();
        const auto& summoner = ability.get_creature();
        int y = start_y + (i / cols) * (box_height + 1);
        int x = start_x + (i % cols) * (box_width + 2);

        bool is_selected = (i == static_cast<size_t>(current_selection));
        bool is_taken = selected[i];

        if (is_selected) {
            attron(A_REVERSE);
        }
        if (is_taken) {
            attron(COLOR_PAIR(2));
        }

        // Draw box borders
        for (int by = 0; by < box_height; ++by) {
            mvhline(y + by, x, ' ', box_width);
        }

        // Draw summoner info (modified)
        mvprintw(y + 1, x + 2, "Name: %s", ability.get_name().c_str());
        mvprintw(y + 2, x + 2, "HP: %zu  Energy: %zu", ability.get_hp(), ability.get_energy());
        mvprintw(y + 3, x + 2, "Experience: %zu", ability.get_experience());
        mvprintw(y + 4, x + 2, "Accum Index: %zu  Range: %zu", summoner.get_damage(), summoner.get_range());

        if (is_taken) {
            mvprintw(y + box_height - 1, x + 2, "[TAKEN]");
        }

        if (is_selected) {
            attroff(A_REVERSE);
        }
        if (is_taken) {
            attroff(COLOR_PAIR(2));
        }
    }

    refresh_display();
}

// ...existing code for other methods...
