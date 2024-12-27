#ifndef DIRECTOR_HPP
#define DIRECTOR_HPP

#include "ability_builder.hpp"
#include "creature_builder.hpp"
#include "school_builder.hpp"

/**
 * @brief Director class for constructing game entities
 * 
 * Provides static methods to construct Creature, Ability, and School
 * objects using their respective builders.
 */
class Director {
  public:
    /**
     * @brief Builds a creature with specified attributes
     * @param creatureName Name of the creature
     * @param speed Movement speed
     * @param damage Attack damage
     * @param range Attack range
     * @param type Creature type
     * @param initiative Initiative value
     * @return Constructed Creature object
     */
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

    /**
     * @brief Builds an ability with specified attributes
     * @param abilityName Name of the ability
     * @param creature Associated creature
     * @param level Required level
     * @param energy Energy cost
     * @param experience Required experience
     * @param hp Health points
     * @return Constructed Ability object
     */
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
