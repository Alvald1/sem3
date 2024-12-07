#ifndef ABILITY_HPP
#define ABILITY_HPP

#include <stdexcept>
#include "../../../utilities/name_id.hpp"
#include "creature.hpp"

class Ability : public NameID {
  private:
    Creature* creature;
    size_t level{0};
    size_t energy{0};
    size_t experience{0};
    size_t count{0};

    static inline size_t next_id{1};

  public:
    explicit Ability(const std::string& name, Creature* creature, size_t level = 0, size_t energy = 0,
                     size_t experience = 0, size_t count = 0)
        : NameID(next_id++, name), creature(creature), level(level), energy(energy), experience(experience),
          count(count) {
        if (!creature) {
            throw std::invalid_argument("Creature cannot be null");
        }
    }

    // Rule of five
    Ability(const Ability&) = default;
    Ability& operator=(const Ability&) = default;
    Ability(Ability&&) noexcept = default;
    Ability& operator=(Ability&&) noexcept = default;
    ~Ability() = default;

    // Getters
    [[nodiscard]] constexpr Creature*
    get_creature() const noexcept {
        return creature;
    }

    [[nodiscard]] constexpr size_t
    get_level() const noexcept {
        return level;
    }

    [[nodiscard]] constexpr size_t
    get_energy() const noexcept {
        return energy;
    }

    [[nodiscard]] constexpr size_t
    get_experience() const noexcept {
        return experience;
    }

    [[nodiscard]] constexpr size_t
    get_count() const noexcept {
        return count;
    }

    // Setters
    constexpr void
    set_creature(Creature* new_creature) noexcept {
        creature = new_creature;
    }

    constexpr void
    set_level(size_t new_level) noexcept {
        level = new_level;
    }

    constexpr void
    set_energy(size_t new_energy) noexcept {
        energy = new_energy;
    }

    constexpr void
    set_experience(size_t new_experience) noexcept {
        experience = new_experience;
    }

    constexpr void
    set_count(size_t new_count) noexcept {
        count = new_count;
    }

    [[nodiscard]] bool
    can_upgrade(size_t exp, size_t level) const {
        return exp >= experience && level >= this->level;
    }

    [[nodiscard]] bool
    has_creature() const noexcept {
        return creature != nullptr;
    }
};

#endif // ABILITY_HPP
