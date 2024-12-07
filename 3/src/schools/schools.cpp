#include "schools.hpp"
#include <algorithm>
#include <numeric>

void Schools::add_school(School school) {
    schools.push_back(std::move(school));
}


size_t Schools::count_schools() const {
    return schools.size();
}

size_t Schools::count_creatures() const {
    return std::accumulate(schools.begin(), schools.end(), size_t{0},
                          [](size_t sum, const School& school) {
                              return sum + school.count_creatures();
                          });
}

std::vector<Ability> Schools::get_available_abilities(std::unordered_map<School, size_t> levels) const {
    std::vector<Ability> result;
    for (const auto& school : schools) {
        auto school_abilities = school.get_available_abilities(levels[school]); // получаем временный объект
        result.insert(result.end(), 
                     std::make_move_iterator(school_abilities.begin()),
                     std::make_move_iterator(school_abilities.end()));
    }
    return std::move(result);
}

std::vector<Ability> Schools::get_upgradable_abilities(size_t exp, std::unordered_map<School, size_t> levels) const {
    std::vector<Ability> result;
    for (const auto& school : schools) {
        auto school_abilities = school.get_upgradable_abilities(exp, levels[school]);
        result.insert(result.end(), 
                     std::make_move_iterator(school_abilities.begin()),
                     std::make_move_iterator(school_abilities.end()));
    }
    return std::move(result);
}

const School* Schools::find_school_by_id(size_t id) const {
    auto it = std::find_if(schools.begin(), schools.end(),
                          [id](const School& school) { return school.get_id() == id; });
    return it != schools.end() ? &(*it) : nullptr;
}

const School* Schools::find_school_by_name(const std::string& name) const {
    auto it = std::find_if(schools.begin(), schools.end(),
                          [&name](const School& school) { return school.get_name() == name; });
    return it != schools.end() ? &(*it) : nullptr;
}

size_t Schools::count_total_abilities() const {
    size_t total = 0;
    for (const auto& school : schools) {
        total += school.get_abilities().size();
    }
    return total;
}

bool Schools::has_school(size_t id) const {
    return find_school_by_id(id) != nullptr;
}

bool Schools::remove_school(size_t id) {
    auto it = std::find_if(schools.begin(), schools.end(),
                          [id](const School& school) { return school.get_id() == id; });
    if (it != schools.end()) {
        schools.erase(it);
        return true;
    }
    return false;
}