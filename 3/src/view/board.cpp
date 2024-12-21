#include "board.hpp"

Board::Board(const Map& game_map) : map(game_map) {
    // Initialize ncurses
    window = initscr();
    noecho();
    cbreak();
    keypad(window, TRUE);
    curs_set(0);
    
    // Initialize colors
    start_color();
    init_colors();
}

Board::~Board() {
    cleanup();
}

void Board::init_colors() {
    init_pair(1, COLOR_WHITE, COLOR_BLACK);   // Empty cell
    init_pair(2, COLOR_RED, COLOR_BLACK);     // Wall/obstacle
    init_pair(3, COLOR_GREEN, COLOR_BLACK);   // Entity
    init_pair(4, COLOR_WHITE, COLOR_BLACK);   // Border
}

void Board::cleanup() {
    endwin();
}

void Board::draw() {
    clear();
    
    auto size = map.get_size();
    Matrix<int> cell_types = map.export_cell_types_matrix();
    
    // Draw top border
    attron(COLOR_PAIR(4));
    mvaddch(0, 0, ACS_ULCORNER);
    for (size_t j = 0; j < size.second; ++j) {
        mvaddch(0, j * 3 + 1, ACS_HLINE);
        mvaddch(0, j * 3 + 2, ACS_HLINE);
        if (j < size.second - 1) mvaddch(0, j * 3 + 3, ACS_TTEE);
    }
    mvaddch(0, size.second * 3, ACS_URCORNER);
    
    // Draw cells and vertical borders
    for (size_t i = 0; i < size.first; ++i) {
        mvaddch(i * 2 + 1, 0, ACS_VLINE);
        
        for (size_t j = 0; j < size.second; ++j) {
            int cell_type = cell_types(i, j);
            switch(cell_type) {
                case 0: // Empty passable cell
                    attron(COLOR_PAIR(1));
                    mvaddch(i * 2 + 1, j * 3 + 2, '.');
                    attroff(COLOR_PAIR(1));
                    break;
                case 1: // Wall/obstacle
                    attron(COLOR_PAIR(2));
                    mvaddch(i * 2 + 1, j * 3 + 2, '#');
                    attroff(COLOR_PAIR(2));
                    break;
                case 2: // Entity present
                    attron(COLOR_PAIR(3));
                    mvaddch(i * 2 + 1, j * 3 + 2, '@');
                    attroff(COLOR_PAIR(3));
                    break;
            }
            attron(COLOR_PAIR(4));
            mvaddch(i * 2 + 1, j * 3 + 3, ACS_VLINE);
        }
        
        // Draw horizontal lines between rows
        if (i < size.first - 1) {
            mvaddch(i * 2 + 2, 0, ACS_LTEE);
            for (size_t j = 0; j < size.second; ++j) {
                mvaddch(i * 2 + 2, j * 3 + 1, ACS_HLINE);
                mvaddch(i * 2 + 2, j * 3 + 2, ACS_HLINE);
                if (j < size.second - 1) mvaddch(i * 2 + 2, j * 3 + 3, ACS_PLUS);
            }
            mvaddch(i * 2 + 2, size.second * 3, ACS_RTEE);
        }
    }
    
    // Draw bottom border
    mvaddch(size.first * 2, 0, ACS_LLCORNER);
    for (size_t j = 0; j < size.second; ++j) {
        mvaddch(size.first * 2, j * 3 + 1, ACS_HLINE);
        mvaddch(size.first * 2, j * 3 + 2, ACS_HLINE);
        if (j < size.second - 1) mvaddch(size.first * 2, j * 3 + 3, ACS_BTEE);
    }
    mvaddch(size.first * 2, size.second * 3, ACS_LRCORNER);
    attroff(COLOR_PAIR(4));
}

void Board::refresh_display() {
    refresh();
}
