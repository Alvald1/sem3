
#include "ability.hpp"
#include "schools/builders/ability_builder.hpp"

AbilityBuilder
Ability::create(std::string name, Creature creature) {
    return AbilityBuilder(std::move(name), std::move(creature));
}