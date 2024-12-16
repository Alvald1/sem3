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
    std::set<const Creature*, std::less<>> unique_creatures;
    for (const auto& school : schools) {
        for (const auto& ability : school.get_abilities()) {
            unique_creatures.insert(ability.get_creature());
        }
    }
    return unique_creatures.size();
}

std::vector<Ability>
Schools::get_available_abilities(const std::unordered_map<size_t, size_t>& levels, size_t energy) const {
    std::vector<Ability> result;
    for (const auto& school : schools) {
        auto it = levels.find(school.get_id());
        if (it != levels.end()) {
            auto school_abilities = school.get_available_abilities(it->second, energy);
            result.insert(result.end(), std::make_move_iterator(school_abilities.begin()),
                          std::make_move_iterator(school_abilities.end()));
        }
    }
    return result; // Removed std::move
}

std::vector<Ability>
Schools::get_upgradable_abilities(const std::unordered_map<size_t, size_t>& levels, size_t exp) const {
    std::vector<Ability> result;
    for (const auto& school : schools) {
        auto it = levels.find(school.get_id());
        if (it != levels.end()) {
            // Corrected parameter order: level first, then exp
            auto school_abilities = school.get_upgradable_abilities(it->second, exp);
            result.insert(result.end(), std::make_move_iterator(school_abilities.begin()),
                          std::make_move_iterator(school_abilities.end()));
        }
    }
    return result; // Removed std::move
}

const School*
Schools::find_school_by_id(size_t id) const {
    auto it =
        std::find_if(schools.begin(), schools.end(), [id](const School& school) { return school.get_id() == id; });
    return it != schools.end() ? &(*it) : nullptr;
}

const School*
Schools::find_school_by_name(const std::string& name) const {
    auto it = std::find_if(schools.begin(), schools.end(),
                           [&name](const School& school) { return school.get_name() == name; });
    return it != schools.end() ? &(*it) : nullptr;
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
    return find_school_by_id(id) != nullptr;
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