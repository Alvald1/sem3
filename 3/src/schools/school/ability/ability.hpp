#ifndef ABILITY_HPP
#define ABILITY_HPP

#include "creature.hpp"
#include "utilities/name_id.hpp"

class Ability : public NameID {
  private:
    Creature* creature{nullptr};
    size_t level{0};
    size_t energy{0};
    size_t upgrade_index{0};
    size_t experience{0};

    static inline size_t id_counter{0};

  public:
    explicit Ability(const std::string& name, size_t level = 0, size_t energy = 0, size_t upgrade_index = 0,
                     size_t experience = 0, Creature* creature = nullptr)
        : NameID(++id_counter, name), creature(creature), level(level), energy(energy), upgrade_index(upgrade_index),
          experience(experience) {}

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
    get_upgrade_index() const noexcept {
        return upgrade_index;
    }

    [[nodiscard]] constexpr size_t
    get_experience() const noexcept {
        return experience;
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
    set_upgrade_index(size_t new_upgrade_index) noexcept {
        upgrade_index = new_upgrade_index;
    }

    constexpr void
    set_experience(size_t new_experience) noexcept {
        experience = new_experience;
    }
};

#endif // ABILITY_HPP
