#include "game_manager.hpp"

#include <iostream>

void
GameManager::do_step() {
    MapManager::getInstance().effect_cells();
    auto cur_entity = EntityManager::getInstance().get_current_entity();
    if (cur_entity == nullptr) {
        return;
    }
}
