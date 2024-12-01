#ifndef SCHOOLS_HPP
#define SCHOOLS_HPP

#include <vector>
#include "../ability/ability.hpp"
#include "../school/school.hpp"
#include "../utils/hash_table.hpp"
#include "../experience/experience.hpp"

class Schools {
private:
    std::vector<School> schools;

public:
    void add_school(School school);
    size_t count_schools() const;
    size_t count_creatures() const;
    Vector<Ability> get_available_abilities(HashT<School, Level> levels) const;
    Vector<Ability> get_upgradable_abilities(Experience exp, HashT<School, Level> levels) const;
};

#endif // SCHOOLS_HPP
