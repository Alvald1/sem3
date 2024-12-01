
#include "school.hpp"

School::School(size_t id, const std::string& name) : NameID(id, name) {}

void School::add_ability(const Ability& ability) {
    abilities.push_back(ability);
}

Vector<Ability> School::get_available_abilities(Level level) const {
    Vector<Ability> available;
    for (const auto& ability : abilities) {
        if (ability.get_required_level() <= level) {
            available.push_back(ability);
        }
    }
    return available;
}

Vector<Ability> School::get_upgradable_abilities(const Experience& exp, Level level) const {
    Vector<Ability> upgradable;
    for (const auto& ability : abilities) {
        if (ability.can_upgrade(exp, level)) {
            upgradable.push_back(ability);
        }
    }
    return upgradable;
}