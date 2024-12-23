#include "creature_builder.hpp"
#include "schools/school/ability/creature.hpp"

CreatureBuilder::CreatureBuilder(std::string name) : creature_(std::move(name)) {}

CreatureBuilder&
CreatureBuilder::speed(size_t value) {
    creature_.speed = value;
    return *this;
}

CreatureBuilder&
CreatureBuilder::damage(size_t value) {
    creature_.damage = value;
    return *this;
}

CreatureBuilder&
CreatureBuilder::range(size_t value) {
    creature_.range = value;
    return *this;
}

CreatureBuilder&
CreatureBuilder::type(size_t value) {
    creature_.type = value;
    return *this;
}

CreatureBuilder&
CreatureBuilder::initiative(size_t value) {
    creature_.initiative = value;
    return *this;
}

Creature
CreatureBuilder::build() {
    return std::move(creature_);
}
