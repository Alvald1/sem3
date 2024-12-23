
#include "creature.hpp"
#include "schools/builders/creature_builder.hpp"

CreatureBuilder
Creature::create(std::string name) {
    return CreatureBuilder(std::move(name));
}