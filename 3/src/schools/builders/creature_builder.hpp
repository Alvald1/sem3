#ifndef CREATURE_BUILDER_HPP
#define CREATURE_BUILDER_HPP

#include "schools/school/ability/creature.hpp"

class CreatureBuilder {
  private:
    Creature creature;

  public:
    explicit CreatureBuilder(std::string name) : creature(std::move(name)) {}

    CreatureBuilder&
    set_speed(size_t speed) {
        creature.set_speed(speed);
        return *this;
    }

    CreatureBuilder&
    set_damage(size_t damage) {
        creature.set_damage(damage);
        return *this;
    }

    CreatureBuilder&
    set_range(size_t range) {
        creature.set_range(range);
        return *this;
    }

    CreatureBuilder&
    set_type(size_t type) {
        creature.set_type(type);
        return *this;
    }

    CreatureBuilder&
    set_initiative(size_t initiative) {
        creature.set_initiative(initiative);
        return *this;
    }

    [[nodiscard]] Creature
    build() const {
        return creature;
    }
};

#endif // CREATURE_BUILDER_HPP
