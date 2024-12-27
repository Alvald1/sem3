#include "schools.hpp"

#include <algorithm>
#include <numeric>
#include <set>

void
Schools::add_school(School school) {
    schools.push_back(std::move(school));
}

size_t
Schools::count_schools() const {
    return schools.size();
}

size_t
Schools::count_creatures() const {
    std::set<Creature, std::less<>> unique_creatures;
    for (const auto& school : schools) {
        for (const auto& ability : school.get_abilities()) {
            unique_creatures.insert(ability.get_creature());
        }
    }
    return unique_creatures.size();
}

std::vector<std::reference_wrapper<const Ability>>
Schools::get_available_abilities(const std::unordered_map<size_t, size_t>& levels, size_t energy) const {
    std::vector<std::reference_wrapper<const Ability>> result;
    for (const auto& school : schools) {
        auto it = levels.find(school.get_id());
        if (it != levels.end()) {
            auto school_abilities = school.get_available_abilities(it->second, energy);
            for (const auto& ability : school_abilities) {
                if (ability.get().get_creature().get_type() != 0) {
                    result.push_back(ability);
                }
            }
        }
    }
    return result;
}

std::vector<std::reference_wrapper<const Ability>>
Schools::get_upgradable_abilities(const std::unordered_map<size_t, size_t>& levels, size_t exp) const {
    std::vector<std::reference_wrapper<const Ability>> result;
    for (const auto& school : schools) {
        auto it = levels.find(school.get_id());
        if (it != levels.end()) {
            auto school_abilities = school.get_upgradable_abilities(it->second, exp);
            for (const auto& ability : school_abilities) {
                if (ability.get().get_creature().get_type() != 0) {
                    result.push_back(ability);
                }
            }
        }
    }
    return result;
}

std::optional<std::reference_wrapper<const School>>
Schools::find_school_by_id(size_t id) const {
    auto it =
        std::find_if(schools.begin(), schools.end(), [id](const School& school) { return school.get_id() == id; });
    return it != schools.end() ? std::optional<std::reference_wrapper<const School>>(std::cref(*it)) : std::nullopt;
}

std::optional<std::reference_wrapper<const School>>
Schools::find_school_by_name(const std::string& name) const {
    auto it = std::find_if(schools.begin(), schools.end(),
                           [&name](const School& school) { return school.get_name() == name; });
    return it != schools.end() ? std::optional<std::reference_wrapper<const School>>(std::cref(*it)) : std::nullopt;
}

std::optional<std::reference_wrapper<const School>>
Schools::find_school_by_ability_id(size_t ability_id) const {
    for (const auto& school : schools) {
        if (school.has_ability(ability_id)) {
            return std::cref(school);
        }
    }
    return std::nullopt;
}

size_t
Schools::count_total_abilities() const {
    size_t total = 0;
    for (const auto& school : schools) {
        total += school.get_abilities().size();
    }
    return total;
}

bool
Schools::has_school(size_t id) const {
    return find_school_by_id(id).has_value();
}

bool
Schools::remove_school(size_t id) {
    auto it =
        std::find_if(schools.begin(), schools.end(), [id](const School& school) { return school.get_id() == id; });
    if (it != schools.end()) {
        schools.erase(it);
        return true;
    }
    return false;
}

std::vector<std::reference_wrapper<const Ability>>
Schools::find_summoner_abilities() const {
    std::vector<std::reference_wrapper<const Ability>> summoner_abilities;
    for (const auto& school : schools) {
        for (const auto& ability : school.get_abilities()) {
            if (ability.get_creature().get_type() == 0) {
                summoner_abilities.push_back(std::cref(ability));
            }
        }
    }
    return summoner_abilities;
}