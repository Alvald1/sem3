#include <iostream>
#include "map/map.hpp"
#include "ui/board.hpp"
#include "ui/control.hpp"
#include "ui/view.hpp"

int
main() {
    try {
        auto& view = View::getInstance();
        auto& control = Control::getInstance();

        // Show menu and get map size
        view.show_menu();
        auto [width, height] = control.get_map_size();

        // Check if user wants to exit
        if (width == 0 && height == 0) {
            return 0;
        }

        // Create and initialize map
        Map game_map;
        game_map.make_map({width, height});

        // Initialize with all passable cells
        Matrix<bool> walls(width, height, true);
        game_map.load_from_passability_matrix(walls);

        // Create board for game display
        Board board(game_map);

        // Main game loop
        while (control.handle_input()) {
            board.draw();
            board.refresh_display();
        }

        return 0;
    } catch (const std::exception& e) {
        endwin();
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
