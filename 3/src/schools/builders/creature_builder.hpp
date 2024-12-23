#ifndef CREATURE_BUILDER_HPP
#define CREATURE_BUILDER_HPP

#include <string>
#include "schools/school/ability/creature.hpp" // Changed from forward declaration

class CreatureBuilder {
  public:
    explicit CreatureBuilder(std::string name);
    CreatureBuilder& speed(size_t value);
    CreatureBuilder& damage(size_t value);
    CreatureBuilder& range(size_t value);
    CreatureBuilder& type(size_t value);
    CreatureBuilder& initiative(size_t value);
    Creature build();

  private:
    Creature creature_;
};

#endif // CREATURE_BUILDER_HPP
