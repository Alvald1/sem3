#include "school.hpp"
#include <algorithm>

School::School(const std::string& name) : NameID(next_id++, name) {}

void
School::add_ability(const Ability& ability) {
    if (!has_ability(ability.get_id())) {
        abilities.push_back(ability);
    }
}

const std::vector<Ability>&
School::get_available_abilities(size_t level) const {
    static std::vector<Ability> available;
    available.clear();
    std::copy_if(abilities.begin(), abilities.end(), std::back_inserter(available),
                 [level](const Ability& a) { return a.get_level() <= level; });
    return available;
}

const std::vector<Ability>&
School::get_upgradable_abilities(size_t exp, size_t level) const {
    static std::vector<Ability> upgradable;
    upgradable.clear();
    std::copy_if(abilities.begin(), abilities.end(), std::back_inserter(upgradable),
                 [exp, level](const Ability& a) { return a.can_upgrade(exp, level); });
    return upgradable;
}

std::optional<const Ability&>
School::find_ability_by_id(size_t id) const {
    auto it = std::find_if(abilities.begin(), abilities.end(), [id](const Ability& a) { return a.get_id() == id; });
    if (it != abilities.end()) {
        return *it;
    }
    return std::nullopt;
}

bool
School::has_ability(size_t id) const {
    return std::any_of(abilities.begin(), abilities.end(), [id](const Ability& a) { return a.get_id() == id; });
}