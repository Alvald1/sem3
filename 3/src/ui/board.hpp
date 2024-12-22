#ifndef BOARD_HPP
#define BOARD_HPP

#include <ncurses.h>
#include "../map/map.hpp"

class Board {
private:
    WINDOW* window;
    const Map& map;
    
    void init_colors();
    void cleanup();

public:
    explicit Board(const Map& game_map);
    ~Board();

    void draw();
    void refresh_display();
};

#endif // BOARD_HPP
