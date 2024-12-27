#include "game_manager.hpp"

#include <iostream>

#include "action_manager.hpp"

void
GameManager::do_step() {
    MapManager::getInstance().effect_cells();
    auto cur_entity = EntityManager::getInstance().get_current_entity();
    if (cur_entity == nullptr) {
        return;
    }
    ActionManager::getInstance().action(*cur_entity);
    EntityManager::getInstance().next_turn();
}
