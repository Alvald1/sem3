#ifndef BOARD_HPP
#define BOARD_HPP

#include <ncurses.h>
#include "map/map.hpp"
#include "ui/view.hpp"

class Board {
  private:
    static const int CELL_WIDTH = 13;       // Увеличиваем для многострочных иконок
    static const int CELL_HEIGHT = 7;       // Высота клетки для лучших пропорций
    static const int INFO_PANEL_WIDTH = 32; // Увеличил ширину для красивого отображения
    static const int QUEUE_BOX_HEIGHT = 4; // Увеличил высоту для доп. информации
    static const int QUEUE_BOX_WIDTH = 30; // Увеличил ширину для HP bar
    size_t offset_x = 0;                   // Horizontal scroll offset
    size_t offset_y = 0;                   // Vertical scroll offset

    WINDOW* window;
    WINDOW* info_window; // Added: window for info panel
    const Map& map;
    View& view;

    void init_colors();
    void cleanup();
    void draw_info_panel(); // Added: method to draw info panel

  public:
    explicit Board(const Map& game_map);
    ~Board();

    void draw();
    void refresh_display();
    void scroll_up();
    void scroll_down();
    void scroll_left();
    void scroll_right();
};

#endif // BOARD_HPP
