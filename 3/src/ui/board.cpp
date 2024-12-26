#include "board.hpp"
#include <string>
#include "managers/entity_manager.hpp"

Board::Board(const Map& game_map) : map(game_map), view(View::getInstance()), offset_x(0), offset_y(0) {
    // Полностью очищаем экран перед созданием окна
    clear();
    refresh();

    // Calculate window sizes and positions
    int map_height = map.get_size().first * CELL_HEIGHT + 1;
    int map_width = map.get_size().second * CELL_WIDTH + 1;

    // Create both windows
    window = newwin(map_height, map_width, 0, 0);
    info_window = newwin(map_height, INFO_PANEL_WIDTH, 0, map_width + 1);

    init_colors();

    // Initial borders
    box(window, 0, 0);
    box(info_window, 0, 0);
}

Board::~Board() {
    delwin(info_window);
    cleanup();
}

void
Board::init_colors() {
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);  // Empty cell
    init_pair(2, COLOR_GREEN, COLOR_BLACK);  // Friendly unit
    init_pair(3, COLOR_RED, COLOR_BLACK);    // Enemy unit
    init_pair(4, COLOR_YELLOW, COLOR_BLACK); // Neutral unit
}

void
Board::draw_info_panel() {
    if (!info_window) {
        return;
    }

    werase(info_window);
    box(info_window, 0, 0);

    wattron(info_window, A_BOLD);
    mvwprintw(info_window, 0, (INFO_PANEL_WIDTH - 7) / 2, " QUEUE ");
    wattroff(info_window, A_BOLD);

    auto entities = EntityManager::getInstance().get_queue_entities();
    if (entities.empty()) {
        mvwprintw(info_window, 2, 2, "Queue is empty");
        wrefresh(info_window);
        return;
    }

    int start_y = 1;
    for (size_t i = 0; i < entities.size(); ++i) {
        if (!entities[i]) {
            continue;
        }

        int box_y = start_y + i * (QUEUE_BOX_HEIGHT + 1);
        if (box_y + QUEUE_BOX_HEIGHT >= getmaxy(info_window)) {
            break;
        }

        // Текущий активный entity выделяем цветом
        bool is_current = (i == 0);
        if (is_current) {
            wattron(info_window, COLOR_PAIR(2) | A_BOLD);
        }

        // Рисуем рамку с красивыми углами
        mvwaddch(info_window, box_y, 1, ACS_ULCORNER);
        mvwaddch(info_window, box_y, QUEUE_BOX_WIDTH, ACS_URCORNER);
        mvwaddch(info_window, box_y + QUEUE_BOX_HEIGHT - 1, 1, ACS_LLCORNER);
        mvwaddch(info_window, box_y + QUEUE_BOX_HEIGHT - 1, QUEUE_BOX_WIDTH, ACS_LRCORNER);

        // Горизонтальные линии
        mvwhline(info_window, box_y, 2, ACS_HLINE, QUEUE_BOX_WIDTH - 2);
        mvwhline(info_window, box_y + QUEUE_BOX_HEIGHT - 1, 2, ACS_HLINE, QUEUE_BOX_WIDTH - 2);

        // Вертикальные линии
        for (int y = box_y + 1; y < box_y + QUEUE_BOX_HEIGHT - 1; y++) {
            mvwaddch(info_window, y, 1, ACS_VLINE);
            mvwaddch(info_window, y, QUEUE_BOX_WIDTH, ACS_VLINE);
        }

        // Имя entity по центру
        std::string name = entities[i]->get_name();
        if (name.length() > QUEUE_BOX_WIDTH - 4) {
            name = name.substr(0, QUEUE_BOX_WIDTH - 7) + "...";
        }
        int name_x = 2 + (QUEUE_BOX_WIDTH - 2 - name.length()) / 2;
        mvwprintw(info_window, box_y + 1, name_x, "%s", name.c_str());

        // HP bar и значение
        int hp_width = QUEUE_BOX_WIDTH - 8;
        double hp_percent = entities[i]->get_health_percentage();
        int filled_width = static_cast<int>(hp_width * hp_percent / 100.0);

        mvwprintw(info_window, box_y + 2, 3, "HP:");
        if (!is_current) {
            wattron(info_window, COLOR_PAIR(3)); // Красный для пустой части
        }
        mvwhline(info_window, box_y + 2, 6, '=', hp_width);
        if (!is_current) {
            wattroff(info_window, COLOR_PAIR(3));
            wattron(info_window, COLOR_PAIR(2)); // Зеленый для заполненной части
        }
        mvwhline(info_window, box_y + 2, 6, '#', filled_width);
        if (!is_current) {
            wattroff(info_window, COLOR_PAIR(2));
        }

        // Числовое значение HP
        mvwprintw(info_window, box_y + 2, QUEUE_BOX_WIDTH - 8, "%zu/%zu", static_cast<size_t>(entities[i]->get_hp()),
                  static_cast<size_t>(entities[i]->get_max_hp()));

        if (is_current) {
            wattroff(info_window, COLOR_PAIR(2) | A_BOLD);
        }
    }

    wrefresh(info_window);
}

void
Board::draw() {
    werase(window);

    // Get map dimensions and current entity
    auto [map_height, map_width] = map.get_size();
    auto current_entity = EntityManager::getInstance().get_current_entity();

    // Calculate visible rows and columns based on window size
    const size_t visible_rows = std::min(static_cast<size_t>(LINES / CELL_HEIGHT), map_height);
    const size_t visible_cols = std::min(static_cast<size_t>(COLS / CELL_WIDTH), map_width);

    // Убедимся, что offset не выходит за пределы
    offset_x = std::min(offset_x, map_width > 0 ? map_width - 1 : 0);
    offset_y = std::min(offset_y, map_height > 0 ? map_height - 1 : 0);

    size_t row_end = std::min(offset_y + visible_rows, map_height);
    size_t col_end = std::min(offset_x + visible_cols, map_width);

    // Find current entity position first
    Matrix<size_t> entity_ids = map.export_entity_ids_matrix();
    Position current_pos;
    bool found_current = false;
    if (current_entity) {
        for (size_t y = 0; y < map_height && !found_current; y++) {
            for (size_t x = 0; x < map_width; x++) {
                if (entity_ids(y, x) == current_entity->get_id()) {
                    current_pos = Position(x, y);
                    found_current = true;
                    break;
                }
            }
        }
    }

    // Draw the basic grid first
    for (size_t y = offset_y; y <= row_end; y++) {
        for (size_t x = offset_x; x <= col_end; x++) {
            int grid_y = (y - offset_y) * CELL_HEIGHT;
            int grid_x = (x - offset_x) * CELL_WIDTH;

            // Draw standard cell borders
            if (x < map_width) {
                mvwhline(window, grid_y, grid_x, ACS_HLINE, CELL_WIDTH);
            }
            if (y < map_height) {
                mvwvline(window, grid_y, grid_x, ACS_VLINE, CELL_HEIGHT);
            }

            // Draw standard corners
            if (x < map_width && y < map_height) {
                mvwaddch(window, grid_y, grid_x,
                         y == 0 && x == 0 ? ACS_ULCORNER
                         : y == 0         ? ACS_TTEE
                         : x == 0         ? ACS_LTEE
                                          : ACS_PLUS);
            }
        }
    }

    // Draw the highlighted cell for current entity separately
    if (found_current && current_pos.get_x() >= offset_x && current_pos.get_x() < col_end
        && current_pos.get_y() >= offset_y && current_pos.get_y() < row_end) {

        int grid_y = (current_pos.get_y() - offset_y) * CELL_HEIGHT;
        int grid_x = (current_pos.get_x() - offset_x) * CELL_WIDTH;

        wattron(window, COLOR_PAIR(2) | A_BOLD);

        // Draw complete cell border
        // Top and bottom borders
        mvwhline(window, grid_y, grid_x, ACS_HLINE, CELL_WIDTH + 1);
        mvwhline(window, grid_y + CELL_HEIGHT, grid_x, ACS_HLINE, CELL_WIDTH + 1);

        // Left and right borders
        for (int i = 0; i <= CELL_HEIGHT; i++) {
            mvwaddch(window, grid_y + i, grid_x, ACS_VLINE);
            mvwaddch(window, grid_y + i, grid_x + CELL_WIDTH, ACS_VLINE);
        }

        // Corners
        mvwaddch(window, grid_y, grid_x, ACS_ULCORNER);
        mvwaddch(window, grid_y, grid_x + CELL_WIDTH, ACS_URCORNER);
        mvwaddch(window, grid_y + CELL_HEIGHT, grid_x, ACS_LLCORNER);
        mvwaddch(window, grid_y + CELL_HEIGHT, grid_x + CELL_WIDTH, ACS_LRCORNER);

        wattroff(window, COLOR_PAIR(2) | A_BOLD);
    }

    // Draw entities, again restricting to visible section
    for (size_t y = offset_y; y < row_end; y++) {
        for (size_t x = offset_x; x < col_end; x++) {
            if (entity_ids(y, x) != 0) {
                const std::string& icon = view.get_ability_icon(entity_ids(y, x));

                // Split icon into lines
                std::vector<std::string> lines;
                std::string current_line;
                size_t max_line_width = 0;

                for (char c : icon) {
                    if (c == '\n') {
                        if (!current_line.empty()) {
                            max_line_width = std::max(max_line_width, current_line.length());
                            lines.push_back(current_line);
                            current_line.clear();
                        }
                    } else if (c != '\r') {
                        current_line += c;
                    }
                }
                if (!current_line.empty()) {
                    max_line_width = std::max(max_line_width, current_line.length());
                    lines.push_back(current_line);
                }

                // Calculate exact vertical centering
                int cell_start_y = (y - offset_y) * CELL_HEIGHT;
                int total_content_height = lines.size();
                int padding_top = (CELL_HEIGHT - total_content_height) / 2;
                if (padding_top < 1) {
                    padding_top = 1; // Minimum top padding
                }

                // Draw each line centered horizontally
                wattron(window, COLOR_PAIR(2));
                for (size_t i = 0; i < lines.size() && i < CELL_HEIGHT; i++) {
                    const std::string& line = lines[i];
                    int x_padding = (CELL_WIDTH - line.length()) / 2;
                    if (x_padding < 1) {
                        x_padding = 1;
                    }

                    mvwprintw(window, cell_start_y + padding_top + i, (x - offset_x) * CELL_WIDTH + x_padding, "%s",
                              line.c_str());
                }
                wattroff(window, COLOR_PAIR(2));
            }
        }
    }

    // Draw final borders
    for (size_t y = offset_y; y < row_end; y++) {
        mvwaddch(window, (y - offset_y) * CELL_HEIGHT, (col_end - offset_x) * CELL_WIDTH, ACS_RTEE);
    }
    for (size_t x = offset_x; x < col_end; x++) {
        mvwaddch(window, (row_end - offset_y) * CELL_HEIGHT, (x - offset_x) * CELL_WIDTH, ACS_BTEE);
    }

    mvwaddch(window, (row_end - offset_y) * CELL_HEIGHT, (col_end - offset_x) * CELL_WIDTH, ACS_LRCORNER);
    mvwaddch(window, 0, (col_end - offset_x) * CELL_WIDTH, ACS_URCORNER);
    mvwaddch(window, (row_end - offset_y) * CELL_HEIGHT, 0, ACS_LLCORNER);

    // Draw borders
    box(window, 0, 0);

    // Draw info panel и сразу делаем refresh
    draw_info_panel();
    wrefresh(window);
}

void
Board::refresh_display() {
    wrefresh(window);
    wrefresh(info_window);
}

void
Board::cleanup() {
    delwin(window);
}

void
Board::scroll_up() {
    if (offset_y > 0) {
        --offset_y;
    }
}

void
Board::scroll_down() {
    if (offset_y < map.get_size().first) {
        ++offset_y;
    }
}

void
Board::scroll_left() {
    if (offset_x > 0) {
        --offset_x;
    }
}

void
Board::scroll_right() {
    if (offset_x < map.get_size().second) {
        ++offset_x;
    }
}
