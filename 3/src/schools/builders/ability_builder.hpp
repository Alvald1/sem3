#ifndef ABILITY_BUILDER_HPP
#define ABILITY_BUILDER_HPP

#include <string>
#include "schools/school/ability/creature.hpp"

class Ability; // Forward declaration

class AbilityBuilder {
  private:
    Ability* ability_;

  public:
    explicit AbilityBuilder(std::string name, Creature creature);

    AbilityBuilder& level(size_t value) noexcept;
    AbilityBuilder& energy(size_t value) noexcept;
    AbilityBuilder& experience(size_t value) noexcept;
    AbilityBuilder& count(size_t value) noexcept;

    [[nodiscard]] Ability build() const;
};

#endif // ABILITY_BUILDER_HPP
