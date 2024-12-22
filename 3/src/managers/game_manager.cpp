#include "game_manager.hpp"
#include <iostream>

void
GameManager::do_step() {
    map_manager_.effect_cells();
    auto cur_entity = entity_manager_.get_current_entity();
    if (cur_entity == nullptr) {
        return;
    }
}
