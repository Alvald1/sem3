#include "school.hpp"
#include <algorithm>

School::School(const std::string& name) : NameID(next_id++, name) {}

void
School::add_ability(const Ability& ability) {
    if (!has_ability(ability.get_id())) {
        abilities.push_back(std::move(ability)); // можно использовать перемещение, т.к. ability - копия
    }
}

std::vector<Ability>
School::get_available_abilities(size_t level) const {
    std::vector<Ability> available;
    available.reserve(abilities.size()); // резервируем память для избежания реаллокаций
    for(const auto& ability : abilities) {
        if(ability.get_level() <= level) {
            available.push_back(std::move(ability)); // move из копии
        }
    }
    return std::move(available); // явный move при возврате
}

std::vector<Ability>
School::get_upgradable_abilities(size_t exp, size_t level) const {
    std::vector<Ability> upgradable;
    upgradable.reserve(abilities.size());
    for(const auto& ability : abilities) {
        if(ability.can_upgrade(exp, level)) {
            upgradable.push_back(std::move(ability));
        }
    }
    return std::move(upgradable);
}

std::optional<const Ability&>
School::find_ability_by_id(size_t id) const {
    auto it = std::find_if(abilities.begin(), abilities.end(), 
                          [id](const Ability& a) { return a.get_id() == id; });
    return it != abilities.end() ? std::optional<const Ability&>(*it) : std::nullopt;
}

bool
School::has_ability(size_t id) const {
    return std::any_of(abilities.begin(), abilities.end(), [id](const Ability& a) { return a.get_id() == id; });
}

size_t
School::count_creatures() const {
    return std::count_if(abilities.begin(), abilities.end(),
                        [](const Ability& ability) { return ability.has_creature(); });
}