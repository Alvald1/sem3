#include "control.hpp"
#include <algorithm>
#include <iostream>
#include <limits>

Control* Control::instance = nullptr;

Control*
Control::getInstance() {
    if (instance == nullptr) {
        instance = new Control();
    }
    return instance;
}

void
Control::handleInput() {
    // Implement input handling
}

void
Control::update() {
    // Implement update logic
}

[[nodiscard]] Control::SummonerAction
Control::get_summoner_action() const {
    // TODO: Implement actual UI interaction to get action
    return SummonerAction::ACCUMULATE_ENERGY; // Default return for now
}

[[nodiscard]] size_t
Control::get_ability_choice() const {
    return 1; // Default return for now
}
