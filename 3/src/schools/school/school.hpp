#ifndef SCHOOL_HPP
#define SCHOOL_HPP

#include <vector>
#include "../utilities/name_id.hpp"
#include "../ability/ability.hpp"
#include "../experience/experience.hpp"
#include "../utils/vector.hpp"

class School : public NameID {
private:
    std::vector<Ability> abilities;

public:
    School(size_t id, const std::string& name);
    void add_ability(const Ability& ability);
    Vector<Ability> get_available_abilities(Level level) const;
    Vector<Ability> get_upgradable_abilities(const Experience& exp, Level level) const;
};

#endif // SCHOOL_HPP
