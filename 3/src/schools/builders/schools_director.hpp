#ifndef SCHOOLS_DIRECTOR_HPP
#define SCHOOLS_DIRECTOR_HPP

#include <memory>
#include <string>
#include "schools/builders/ability_builder.hpp"
#include "schools/builders/creature_builder.hpp"
#include "schools/builders/school_builder.hpp"
#include "schools/school/ability/ability.hpp"
#include "schools/school/ability/creature.hpp"
#include "schools/school/school.hpp"

class SchoolsDirector {
  public:
    static Creature createCreature(const std::string& name, size_t speed, size_t damage, size_t range, size_t type,
                                   size_t initiative);
    static Ability createAbility(const std::string& name, Creature creature, size_t level, size_t energy,
                                 size_t experience, size_t count);
    static School createSchool(const std::string& name, const std::vector<Ability>& abilities);
};

#endif // SCHOOLS_DIRECTOR_HPP
