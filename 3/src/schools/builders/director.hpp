#ifndef DIRECTOR_HPP
#define DIRECTOR_HPP

#include "ability_builder.hpp"
#include "creature_builder.hpp"
#include "school_builder.hpp"

class Director {
  public:
    static Creature
    buildCreature(const std::string& creatureName, size_t speed, size_t damage, size_t range, size_t type,
                  size_t initiative) {
        return CreatureBuilder(creatureName)
            .set_speed(speed)
            .set_damage(damage)
            .set_range(range)
            .set_type(type)
            .set_initiative(initiative)
            .build();
    }

    static Ability
    buildAbility(const std::string& abilityName, const Creature& creature, size_t level, size_t energy,
                 size_t experience, size_t hp) {
        return AbilityBuilder(abilityName, creature)
            .set_level(level)
            .set_energy(energy)
            .set_experience(experience)
            .set_hp(hp)
            .build();
    }

    static School
    buildSchool(const std::string& schoolName, const Ability& ability) {
        return SchoolBuilder(schoolName).add_ability(ability).build();
    }
};

#endif // DIRECTOR_HPP
