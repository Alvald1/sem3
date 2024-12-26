#include "board.hpp"
#include <string>

Board::Board(const Map& game_map) : map(game_map), view(View::getInstance()), offset_x(0), offset_y(0) {
    // Полностью очищаем экран перед созданием окна
    clear();
    refresh();

    int height = map.get_size().first * CELL_HEIGHT + 1;
    int width = map.get_size().second * CELL_WIDTH + 1;
    window = newwin(height, width, 0, 0);
    init_colors();
}

Board::~Board() { cleanup(); }

void
Board::init_colors() {
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);  // Empty cell
    init_pair(2, COLOR_GREEN, COLOR_BLACK);  // Friendly unit
    init_pair(3, COLOR_RED, COLOR_BLACK);    // Enemy unit
    init_pair(4, COLOR_YELLOW, COLOR_BLACK); // Neutral unit
}

void
Board::draw() {
    werase(window);

    // Get map dimensions
    auto [map_height, map_width] = map.get_size();

    // Calculate visible rows and columns based on window size
    const size_t visible_rows = LINES / CELL_HEIGHT;
    const size_t visible_cols = COLS / CELL_WIDTH;

    size_t row_end = std::min(offset_y + visible_rows, map_height);
    size_t col_end = std::min(offset_x + visible_cols, map_width);

    // Draw only the visible portion of the grid
    for (size_t y = offset_y; y <= row_end; y++) {
        for (size_t x = offset_x; x <= col_end; x++) {
            // Calculate screen positions
            int grid_y = (y - offset_y) * CELL_HEIGHT;
            int grid_x = (x - offset_x) * CELL_WIDTH;

            if (y < map_height && x < map_width) {
                // Clear cell interior
                for (int i = 1; i < CELL_HEIGHT; i++) {
                    mvwhline(window, grid_y + i, grid_x + 1, ' ', CELL_WIDTH - 1);
                }
            }

            // Draw borders
            if (x < map_width) {
                mvwhline(window, grid_y, grid_x, ACS_HLINE, CELL_WIDTH);
            }
            if (y < map_height) {
                mvwvline(window, grid_y, grid_x, ACS_VLINE, CELL_HEIGHT);
            }

            // Draw corners
            if (x < map_width && y < map_height) {
                mvwaddch(window, grid_y, grid_x,
                         y == 0 && x == 0 ? ACS_ULCORNER
                         : y == 0         ? ACS_TTEE
                         : x == 0         ? ACS_LTEE
                                          : ACS_PLUS);
            }
        }
    }

    // Draw entities, again restricting to visible section
    Matrix<size_t> entity_ids = map.export_entity_ids_matrix();
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

    wrefresh(window);
}

void
Board::refresh_display() {
    wrefresh(window);
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
