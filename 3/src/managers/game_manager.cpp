#include "game_manager.hpp"
#include <iostream>

void
GameManager::do_step() {
    if (!queue_.empty()) {
        auto entity = queue_.front();
        (void)entity;
        // Perform actions with the entity
        // ...existing code...

        // If all actions are successful, shift the queue
        queue_.shift();
    } else {
        std::cerr << "Queue is empty, cannot perform step." << std::endl;
    }
}
