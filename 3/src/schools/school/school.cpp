#include "school.hpp"

#include <algorithm>

void
School::add_ability(Ability ability) {
    if (!has_ability(ability.get_id())) {
        abilities.push_back(std::move(ability));
    }
}

std::vector<std::reference_wrapper<const Ability>>
School::get_available_abilities(size_t level, size_t energy) const {
    std::vector<std::reference_wrapper<const Ability>> available;
    available.reserve(abilities.size());
    for (const auto& ability : abilities) {
        if (ability.get_level() <= level && ability.get_energy() <= energy && ability.get_creature().get_type() != 0) {
            available.push_back(std::cref(ability));
        }
    }
    return available;
}

std::vector<std::reference_wrapper<const Ability>>
School::get_upgradable_abilities(size_t level, size_t exp) const {
    std::vector<std::reference_wrapper<const Ability>> upgradable;
    for (const auto& ability : abilities) {
        if (ability.can_upgrade(exp, level) && ability.get_creature().get_type() != 0) {
            upgradable.push_back(std::cref(ability));
        }
    }
    return upgradable;
}

std::optional<Ability>
School::find_ability_by_id(size_t id) const {
    auto it = std::find_if(abilities.begin(), abilities.end(), [id](const Ability& a) { return a.get_id() == id; });
    return it != abilities.end() ? std::optional<Ability>(*it) : std::nullopt;
}

bool
School::has_ability(size_t id) const {
    return std::any_of(abilities.begin(), abilities.end(), [id](const Ability& a) { return a.get_id() == id; });
}

size_t
School::count_creatures() const {
    std::set<Creature> unique_creatures;
    for (const auto& ability : abilities) {
        unique_creatures.insert(ability.get_creature());
    }
    return unique_creatures.size();
}