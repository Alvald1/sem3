
#include "schools.hpp"

void Schools::add_school(School school) {
    schools.push_back(school);
}

size_t Schools::count_schools() const {
    return schools.size();
}

size_t Schools::count_creatures() const {
    size_t total = 0;
    for (const auto& school : schools) {
        total += school.count_creatures();
    }
    return total;
}

Vector<Ability> Schools::get_available_abilities(HashT<School, Level> levels) const {
    Vector<Ability> available;
    for (const auto& school : schools) {
        Vector<Ability> school_abilities = school.get_available_abilities(levels);
        available.append(school_abilities);
    }
    return available;
}

Vector<Ability> Schools::get_upgradable_abilities(Experience exp, HashT<School, Level> levels) const {
    Vector<Ability> upgradable;
    for (const auto& school : schools) {
        Vector<Ability> school_abilities = school.get_upgradable_abilities(exp, levels);
        upgradable.append(school_abilities);
    }
    return upgradable;
}