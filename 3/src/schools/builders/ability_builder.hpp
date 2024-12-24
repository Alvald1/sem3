#ifndef ABILITY_BUILDER_HPP
#define ABILITY_BUILDER_HPP

#include "creature_builder.hpp"
#include "schools/school/ability/ability.hpp"

class AbilityBuilder {
  private:
    Ability ability;

  public:
    AbilityBuilder(std::string name, Creature creature) : ability(std::move(name), std::move(creature)) {}

    AbilityBuilder&
    set_level(size_t level) {
        ability.set_level(level);
        return *this;
    }

    AbilityBuilder&
    set_energy(size_t energy) {
        ability.set_energy(energy);
        return *this;
    }

    AbilityBuilder&
    set_experience(size_t experience) {
        ability.set_experience(experience);
        return *this;
    }

    AbilityBuilder&
    set_count(size_t count) {
        ability.set_count(count);
        return *this;
    }

    [[nodiscard]] Ability
    build() const {
        return ability;
    }
};

#endif // ABILITY_BUILDER_HPP
