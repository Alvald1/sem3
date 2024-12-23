#include "ability_builder.hpp"
#include "../school/ability/ability.hpp"

AbilityBuilder::AbilityBuilder(std::string name, Creature creature) {
    ability_ = new Ability(std::move(name), std::move(creature));
}

AbilityBuilder&
AbilityBuilder::level(size_t value) noexcept {
    ability_->set_level(value);
    return *this;
}

AbilityBuilder&
AbilityBuilder::energy(size_t value) noexcept {
    ability_->set_energy(value);
    return *this;
}

AbilityBuilder&
AbilityBuilder::experience(size_t value) noexcept {
    ability_->set_experience(value);
    return *this;
}

AbilityBuilder&
AbilityBuilder::count(size_t value) noexcept {
    ability_->set_count(value);
    return *this;
}

Ability
AbilityBuilder::build() const {
    return *ability_;
}

// Remove duplicate implementation of Ability::create since it's now in the right place
// Remove or comment out:
// AbilityBuilder
// Ability::create(std::string name, Creature creature) {
//     return AbilityBuilder(std::move(name), std::move(creature));
// }
