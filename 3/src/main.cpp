#include <iostream>
#include "game/game.hpp"

#include "managers/singleton_manager.hpp"

int
main() {
    try {
        SingletonManager::initializeAll();
        Game game;
        game.start();
        SingletonManager::destroyAll();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
