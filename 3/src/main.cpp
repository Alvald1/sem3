#include <iostream>
#include "map/map.hpp"
#include "ui/board.hpp"

int
main() {
    try {
        // Create map 10x20
        Map game_map;
        game_map.make_map({10, 10});

        // Create some walls and entities for demonstration
        Matrix<bool> walls(10, 10, true); // Start with all passable

        // Add some walls (false means impassable)
        walls(2, 3) = false;
        walls(2, 4) = false;
        walls(3, 3) = false;

        game_map.load_from_passability_matrix(walls);

        // Add some entities (set cells as busy)
        game_map.get_matrix()(5, 5)->set_busy(true);
        game_map.get_matrix()(1, 1)->set_busy(true);
        game_map.get_matrix()(8, 9)->set_busy(true);

        // Create and show board
        Board board(game_map);
        board.draw();
        board.refresh_display();

        // Wait for any key before closing
        getch();

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
