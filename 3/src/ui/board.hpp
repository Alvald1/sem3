#ifndef BOARD_HPP
#define BOARD_HPP

#include <ncurses.h>
#include "map/map.hpp"
#include "ui/view.hpp"

class Board {
  private:
    static Board* instance;
    static const int CELL_WIDTH = 13;       // Увеличиваем для многострочных иконок
    static const int CELL_HEIGHT = 7;       // Высота клетки для лучших пропорций
    static const int INFO_PANEL_WIDTH = 32; // Увеличил ширину для красивого отображения
    static const int QUEUE_BOX_HEIGHT = 4;    // Увеличил высоту для доп. информации
    static const int QUEUE_BOX_WIDTH = 30;    // Увеличил ширину для HP bar
    static const int COMMAND_TEXT_HEIGHT = 2; // Add this constant for command text space
    size_t offset_x = 0;                      // Horizontal scroll offset
    size_t offset_y = 0;                      // Vertical scroll offset

    WINDOW* window;
    WINDOW* info_window; // Added: window for info panel
    const Map& map;
    View& view;

    Position highlighted_cell{0, 0};
    bool has_highlight{false};

    // Make constructor private
    explicit Board(const Map& game_map);
    void init_colors();
    void cleanup();
    void draw_info_panel(); // Added: method to draw info panel

  public:
    // Delete copy constructor and assignment operator
    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;
    ~Board();

    static Board& getInstance(const Map& game_map);

    void highlight_cell(Position pos);
    void clear_highlight();

    void draw();
    void refresh_display();
    void scroll_up();
    void scroll_down();
    void scroll_left();
    void scroll_right();
};

#endif // BOARD_HPP
