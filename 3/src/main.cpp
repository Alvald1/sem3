#include <iostream>
#include "game/game.hpp"

int
main() {
    try {
        Game game;
        game.start();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
