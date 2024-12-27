#ifndef BOARD_HPP
#define BOARD_HPP

#include <ncurses.h>
#include "map/map.hpp"
#include "ui/view.hpp"

/**
 * @brief Board class for rendering the game board
 * 
 * The Board class implements a singleton pattern and handles the rendering
 * of the game board, including entities, effects, and cell highlights.
 */
class Board {
  private:
    /** @brief Width of each cell in characters */
    static const int CELL_WIDTH = 13;
    /** @brief Height of each cell in characters */
    static const int CELL_HEIGHT = 7;
    /** @brief Width of the information panel */
    static const int INFO_PANEL_WIDTH = 32;
    /** @brief Height of queue display boxes */
    static const int QUEUE_BOX_HEIGHT = 4;
    /** @brief Width of queue display boxes */
    static const int QUEUE_BOX_WIDTH = 30;
    /** @brief Height reserved for command text */
    static const int COMMAND_TEXT_HEIGHT = 2;

    /** @brief Horizontal scroll offset */
    size_t offset_x = 0;
    /** @brief Vertical scroll offset */
    size_t offset_y = 0;

    /** @brief Main game window */
    WINDOW* window;
    /** @brief Information panel window */
    WINDOW* info_window;
    /** @brief Reference to game map */
    const Map& map;
    /** @brief Reference to view instance */
    View& view;

    /** @brief Currently highlighted cell position */
    Position highlighted_cell{0, 0};
    /** @brief Whether a cell is currently highlighted */
    bool has_highlight{false};

    /**
     * @brief Private constructor for singleton pattern
     * @param game_map Reference to game map
     */
    explicit Board(const Map& game_map);

    /**
     * @brief Initialize color pairs for NCurses
     */
    void init_colors();

    /**
     * @brief Clean up NCurses windows
     */
    void cleanup();

    /**
     * @brief Draw the information panel
     */
    void draw_info_panel();

  public:
    // Delete copy constructor and assignment operator
    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;
    ~Board();

    /**
     * @brief Get singleton instance of Board
     * @param game_map Reference to game map
     * @return Reference to Board instance
     */
    static Board& getInstance(const Map& game_map);

    /**
     * @brief Highlight a specific cell
     * @param pos Position to highlight
     */
    void highlight_cell(Position pos);

    /**
     * @brief Clear current cell highlight
     */
    void clear_highlight();

    /**
     * @brief Draw the entire game board
     */
    void draw();

    /**
     * @brief Refresh the display
     */
    void refresh_display();

    /**
     * @brief Scroll the view up
     */
    void scroll_up();

    /**
     * @brief Scroll the view down
     */
    void scroll_down();

    /**
     * @brief Scroll the view left
     */
    void scroll_left();

    /**
     * @brief Scroll the view right
     */
    void scroll_right();
};

#endif // BOARD_HPP
