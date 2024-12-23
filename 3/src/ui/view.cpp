#include "view.hpp"

#include <iomanip>
#include <iostream>

View* View::instance = nullptr;

void
View::send_abilities(const std::vector<std::reference_wrapper<const Ability>>& abilities,
                     AbilityDisplayType type) const {
    (void)abilities;
    (void)type;
    // Implement ability display
}
