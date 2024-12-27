#ifndef ABILITY_HPP
#define ABILITY_HPP

#include <memory>

#include "creature.hpp"
#include "utilities/name_id.hpp"

/**
 * @brief Represents a magical ability
 * 
 * An ability is associated with a creature and has various attributes
 * such as level, energy cost, experience requirements, and HP.
 */
class Ability : public NameID {
  private:
    Creature creature;
    size_t level{0};
    size_t energy{0};
    size_t experience{0};
    size_t hp{0};

    static inline size_t next_id{1};

    friend class AbilityBuilder;

  public:
    /**
     * @brief Constructs a new Ability
     * @param name Name of the ability
     * @param creature Associated creature
     */
    explicit Ability(std::string name, Creature creature)
        : NameID(next_id++, std::move(name)), creature(std::move(creature)) {}

    // Rule of five
    Ability(const Ability&) = default;
    Ability& operator=(const Ability&) = default;
    Ability(Ability&&) noexcept = default;
    Ability& operator=(Ability&&) noexcept = default;
    ~Ability() = default;

    /**
     * @brief Gets the associated creature
     * @return Const reference to the creature
     */
    [[nodiscard]] inline const Creature&
    get_creature() const noexcept {
        return creature;
    }

    /**
     * @brief Gets the ability's level requirement
     * @return Required level
     */
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
    get_hp() const noexcept {
        return hp;
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
    set_hp(size_t new_hp) noexcept {
        hp = new_hp;
    }

    /**
     * @brief Checks if the ability can be upgraded
     * @param exp Available experience points
     * @param lvl Current level
     * @return true if can be upgraded, false otherwise
     */
    [[nodiscard]] constexpr bool
    can_upgrade(size_t exp, size_t lvl) const noexcept {
        return exp >= experience && lvl >= level;
    }
};

#endif // ABILITY_HPP
