#ifndef ABILITY_HPP
#define ABILITY_HPP

#include <memory>

#include "creature.hpp"
#include "schools/builders/ability_builder.hpp"
#include "utilities/name_id.hpp"

class AbilityBuilder; // Forward declaration

class Ability : public NameID {
  private:
    Creature creature;
    size_t level{0};
    size_t energy{0};
    size_t experience{0};
    size_t count{0};

    static inline size_t next_id{1};

    friend class AbilityBuilder;

    explicit Ability(std::string name, Creature creature)
        : NameID(next_id++, std::move(name)), creature(std::move(creature)) {}

  public:
    static AbilityBuilder create(std::string name, Creature creature);

    // Rule of five
    Ability(const Ability&) = default;
    Ability& operator=(const Ability&) = default;
    Ability(Ability&&) noexcept = default;
    Ability& operator=(Ability&&) noexcept = default;
    ~Ability() = default;

    // Getters
    [[nodiscard]] inline const Creature&
    get_creature() const noexcept {
        return creature;
    }

    [[nodiscard]] inline size_t
    get_level() const noexcept {
        return level;
    }

    [[nodiscard]] inline size_t
    get_energy() const noexcept {
        return energy;
    }

    [[nodiscard]] inline size_t
    get_experience() const noexcept {
        return experience;
    }

    [[nodiscard]] inline size_t
    get_count() const noexcept {
        return count;
    }

    // Setters
    inline void
    set_creature(Creature new_creature) {
        creature = std::move(new_creature);
    }

    inline void
    set_level(size_t new_level) noexcept {
        level = new_level;
    }

    inline void
    set_energy(size_t new_energy) noexcept {
        energy = new_energy;
    }

    inline void
    set_experience(size_t new_experience) noexcept {
        experience = new_experience;
    }

    inline void
    set_count(size_t new_count) noexcept {
        count = new_count;
    }

    [[nodiscard]] constexpr bool
    can_upgrade(size_t exp, size_t lvl) const noexcept {
        return exp >= experience && lvl >= level;
    }
};

#endif // ABILITY_HPP
