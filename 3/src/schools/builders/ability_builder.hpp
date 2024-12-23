#ifndef ABILITY_BUILDER_HPP
#define ABILITY_BUILDER_HPP

#include <memory>
#include "src/schools/school/ability/ability.hpp"

class AbilityBuilder {
  public:
    AbilityBuilder(std::string name, Creature creature)
        : ability_(std::make_unique<Ability>(std::move(name), std::move(creature))) {}

    AbilityBuilder&
    level(size_t value) {
        ability_->level = value;
        return *this;
    }

    AbilityBuilder&
    energy(size_t value) {
        ability_->energy = value;
        return *this;
    }

    AbilityBuilder&
    experience(size_t value) {
        ability_->experience = value;
        return *this;
    }

    AbilityBuilder&
    count(size_t value) {
        ability_->count = value;
        return *this;
    }

    Ability
    build() {
        return std::move(*ability_);
    }

  private:
    std::unique_ptr<Ability> ability_;
};

#endif // ABILITY_BUILDER_HPP
