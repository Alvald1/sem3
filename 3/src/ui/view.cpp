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
    endwin();
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

    // Display title with proper format string
    mvprintw(0, 0, "%s", get_title(type));

    if (abilities.empty()) {
        mvprintw(2, 0, "%s", get_empty_message(type));
    } else {
        // Display abilities list
        int y = 2;
        for (const auto& ability : abilities) {
            mvprintw(y++, 2, "- %s", ability.get().get_name().c_str());
        }
    }

    refresh_display();
}

// ...existing code for other methods...
