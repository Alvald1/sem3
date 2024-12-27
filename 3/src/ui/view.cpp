#include "view.hpp"
#include <string>

#include "utilities/type_system.hpp"

View* View::instance = nullptr;

View&
View::getInstance() {
    if (instance == nullptr) {
        instance = new View();
    }
    return *instance;
}

View::View() : summoner_info_window(nullptr) { init(); }

View::~View() { cleanup(); }

void
View::init() {
    putenv((char*)"NCURSES_NO_UTF8_ACS=1");
    window = initscr();
    noecho();
    cbreak();
    keypad(window, TRUE);
    curs_set(0);
    start_color();
    init_colors();
    ESCDELAY = 0;
    clear(); // Clear screen at init
    refresh();
}

void
View::init_colors() {
    init_pair(1, COLOR_WHITE, COLOR_BLACK);  // Default/Menu
    init_pair(2, COLOR_RED, COLOR_BLACK);    // For taken/unavailable
    init_pair(3, COLOR_YELLOW, COLOR_BLACK); // For selection highlight
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
    erase(); // Changed from clear() to erase()
    refresh();
}

void
View::refresh_display() const {
    refresh();
}

void
View::cleanup() {
    clear();   // Clear the screen
    refresh(); // Refresh to show the clear screen
    endwin();  // End curses mode

    // Reset terminal completely
    system("reset"); // This ensures terminal is completely reset
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
View::send_abilities(size_t current_energy, size_t current_experience,
                     const std::vector<std::reference_wrapper<const Ability>>& abilities, AbilityDisplayType type,
                     size_t selected_index) const {
    if (!abilities.empty()) {
        int start_y = 6;
        mvprintw(start_y - 3, COLS - INFO_PANEL_WIDTH + 2, "Current Experience: %zu\n", current_experience);
        mvprintw(start_y - 2, COLS - INFO_PANEL_WIDTH + 2, "Current Energy: %zu\n", current_energy);
        mvprintw(start_y - 1, COLS - INFO_PANEL_WIDTH + 2, "%s", get_title(type));

        const int BOX_HEIGHT = 10; // Increased height to accommodate effects
        const int BOX_WIDTH = INFO_PANEL_WIDTH - 4;

        for (size_t i = 0; i < abilities.size(); ++i) {
            const auto& ability = abilities[i].get();
            const auto& creature = ability.get_creature();
            int box_y = start_y + i * (BOX_HEIGHT + 1);

            // Draw box with yellow border for selected ability
            if (i == selected_index) {
                attron(COLOR_PAIR(3) | A_BOLD);
            }

            // Draw box borders
            mvhline(box_y, COLS - INFO_PANEL_WIDTH + 2, ACS_HLINE, BOX_WIDTH);
            mvhline(box_y + BOX_HEIGHT, COLS - INFO_PANEL_WIDTH + 2, ACS_HLINE, BOX_WIDTH);
            mvvline(box_y, COLS - INFO_PANEL_WIDTH + 2, ACS_VLINE, BOX_HEIGHT);
            mvvline(box_y, COLS - INFO_PANEL_WIDTH + BOX_WIDTH + 1, ACS_VLINE, BOX_HEIGHT);

            // Corners
            mvaddch(box_y, COLS - INFO_PANEL_WIDTH + 2, ACS_ULCORNER);
            mvaddch(box_y, COLS - INFO_PANEL_WIDTH + BOX_WIDTH + 1, ACS_URCORNER);
            mvaddch(box_y + BOX_HEIGHT, COLS - INFO_PANEL_WIDTH + 2, ACS_LLCORNER);
            mvaddch(box_y + BOX_HEIGHT, COLS - INFO_PANEL_WIDTH + BOX_WIDTH + 1, ACS_LRCORNER);

            if (i == selected_index) {
                attroff(COLOR_PAIR(3) | A_BOLD);
            }

            // Content (red if not enough energy)
            if (ability.get_energy() > current_energy) {
                attron(COLOR_PAIR(2));
            }
            mvprintw(box_y + 1, COLS - INFO_PANEL_WIDTH + 4, "Name: %s", ability.get_name().c_str());
            mvprintw(box_y + 2, COLS - INFO_PANEL_WIDTH + 4, "Energy Cost: %zu", ability.get_energy());
            mvprintw(box_y + 3, COLS - INFO_PANEL_WIDTH + 4, "Experience Cost: %zu", ability.get_experience());
            mvprintw(box_y + 4, COLS - INFO_PANEL_WIDTH + 4, "ID: %zu", ability.get_id());
            mvprintw(box_y + 5, COLS - INFO_PANEL_WIDTH + 4, "HP: %zu", ability.get_hp());
            mvprintw(box_y + 6, COLS - INFO_PANEL_WIDTH + 4, "Damage: %zu", creature.get_damage());
            mvprintw(box_y + 7, COLS - INFO_PANEL_WIDTH + 4, "Speed: %zu", creature.get_speed());
            mvprintw(box_y + 8, COLS - INFO_PANEL_WIDTH + 4, "Range: %zu", creature.get_range());

            // Display effects
            auto effects = TypeSystem::get_effects(creature.get_type());
            if (!effects.empty()) {
                int effect_x = COLS - INFO_PANEL_WIDTH + 4;
                int effect_y = box_y + 9;
                mvprintw(effect_y, effect_x, "Effects: ");
                effect_x += 9;

                for (const auto& [effect_type, is_positive] : effects) {
                    const char* effect_name;
                    switch (effect_type) {
                        case EffectType::DAMAGE: effect_name = "DMG"; break;
                        case EffectType::SPEED: effect_name = "SPD"; break;
                        case EffectType::RANGE: effect_name = "RNG"; break;
                        case EffectType::HEALTH: effect_name = "HP"; break;
                        default: effect_name = "???"; break;
                    }

                    attron(COLOR_PAIR(is_positive ? 2 : 3));
                    mvprintw(effect_y, effect_x, "%s%c ", effect_name, is_positive ? '+' : '-');
                    attroff(COLOR_PAIR(is_positive ? 2 : 3));
                    effect_x += 5;
                }
            }

            if (ability.get_energy() > current_energy) {
                attroff(COLOR_PAIR(2));
            }
        }
    } else {
        mvprintw(6, COLS - INFO_PANEL_WIDTH + 2, "%s", get_empty_message(type));
    }
    refresh_display();
}

void
View::clear_ability_panel() const {
    // Clear the entire right panel area from top to bottom
    for (int y = 0; y < LINES; ++y) {
        move(y, COLS - INFO_PANEL_WIDTH);
        clrtoeol();
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

void
View::create_error_window(const std::string& message) const {
    // Calculate window dimensions and position
    int width = std::min(static_cast<int>(message.length()) + 4, COLS - 4);
    int height = 5;
    int starty = (LINES - height) / 2;
    int startx = (COLS - width) / 2;

    // Create a new window
    WINDOW* error_win = newwin(height, width, starty, startx);
    box(error_win, 0, 0);

    // Add title
    wattron(error_win, A_BOLD | COLOR_PAIR(2)); // Use red color for error
    mvwprintw(error_win, 0, (width - 7) / 2, " ERROR ");
    wattroff(error_win, A_BOLD | COLOR_PAIR(2));

    // Add message
    mvwprintw(error_win, 2, 2, "%s", message.c_str());

    // Add instruction
    mvwprintw(error_win, height - 2, (width - 23) / 2, "Press any key to close");

    // Show the window
    wrefresh(error_win);

    // Wait for key
    getch();

    // Clean up
    werase(error_win);
    wrefresh(error_win);
    delwin(error_win);

    // Refresh the main display to restore it
    refresh_display();
}

void
View::show_error(const std::string& message) const {
    create_error_window(message);
}

void
View::show_summoner_info(const Summoner& summoner) { // Remove const from method

    // Создаем или пересоздаем окно справа от очереди
    if (summoner_info_window) {
        delwin(summoner_info_window);
    }

    int start_x = COLS - INFO_PANEL_WIDTH - SUMMONER_INFO_WIDTH;
    summoner_info_window = newwin(10, SUMMONER_INFO_WIDTH, 0, start_x);

    // Рисуем рамку и заголовок
    box(summoner_info_window, 0, 0);
    wattron(summoner_info_window, A_BOLD);
    mvwprintw(summoner_info_window, 0, (SUMMONER_INFO_WIDTH - 15) / 2, " SUMMONER INFO ");
    wattroff(summoner_info_window, A_BOLD);

    // Выводим информацию
    mvwprintw(summoner_info_window, 1, 2, "Energy: %zu", summoner.get_energy());
    mvwprintw(summoner_info_window, 2, 2, "Experience: %zu", summoner.get_experience());
    mvwprintw(summoner_info_window, 3, 2, "Range: 2");
    mvwprintw(summoner_info_window, 4, 2, "Accumulation: %zu", summoner.get_accum_index());

    wrefresh(summoner_info_window);
}

void
View::show_troop_info(const BaseTroop& troop) {
    if (troop_info_window) {
        delwin(troop_info_window);
    }

    int start_x = COLS - INFO_PANEL_WIDTH - TROOP_INFO_WIDTH;
    troop_info_window = newwin(10, TROOP_INFO_WIDTH, 0, start_x);

    // Рисуем рамку и заголовок
    box(troop_info_window, 0, 0);
    wattron(troop_info_window, A_BOLD);
    mvwprintw(troop_info_window, 0, (TROOP_INFO_WIDTH - 11) / 2, " TROOP INFO ");
    wattroff(troop_info_window, A_BOLD);

    // Базовая информация
    mvwprintw(troop_info_window, 1, 2, "Damage: %zu", troop.get_damage());
    mvwprintw(troop_info_window, 2, 2, "Speed: %zu", troop.get_speed());
    mvwprintw(troop_info_window, 3, 2, "Range: %zu", troop.get_range());
    mvwprintw(troop_info_window, 4, 2, "Moves left: %zu", troop.get_remaining_movement());

    // Получаем и выводим эффекты
    auto effects = TypeSystem::get_effects(troop.get_type());
    if (!effects.empty()) {
        int line = 7;
        for (const auto& [effect_type, is_positive] : effects) {
            const char* effect_name;
            switch (effect_type) {
                case EffectType::DAMAGE: effect_name = "Damage"; break;
                case EffectType::SPEED: effect_name = "Speed"; break;
                case EffectType::RANGE: effect_name = "Range"; break;
                case EffectType::HEALTH: effect_name = "Health"; break;
                default: effect_name = "Unknown"; break;
            }

            wattron(troop_info_window, COLOR_PAIR(is_positive ? 2 : 3));
            mvwprintw(troop_info_window, line++, 4, "%s (%c)", effect_name, is_positive ? '+' : '-');
            wattroff(troop_info_window, COLOR_PAIR(is_positive ? 2 : 3));
        }
    }

    wrefresh(troop_info_window);
}

// ...existing code for other methods...
