#ifndef BASE_TROOP_HPP
#define BASE_TROOP_HPP

#include "queue/entity/entity.hpp"

/**
 * @brief Base class for all troop entities
 * 
 * Implements common functionality for all troops including movement,
 * combat stats and experience tracking.
 */
class BaseTroop : public Entity {

  private:
    size_t speed;
    size_t damage;
    size_t range;
    size_t type;
    size_t remaining_movement;
    size_t experience;

  protected:
    /**
     * @brief Construct a new Base Troop
     * @param ability The ability that defines troop's base stats
     */
    explicit BaseTroop(const Ability& ability)
        : Entity(ability), speed(ability.get_creature().get_speed()), damage(ability.get_creature().get_damage()),
          range(ability.get_creature().get_range()), type(ability.get_creature().get_type()),
          remaining_movement(ability.get_creature().get_speed()), experience(ability.get_experience()) {}

    size_t id_summoner_;

  public:
    // Rule of five
    BaseTroop(const BaseTroop&) = default;
    BaseTroop& operator=(const BaseTroop&) = default;
    BaseTroop(BaseTroop&&) noexcept = default;
    BaseTroop& operator=(BaseTroop&&) noexcept = default;
    ~BaseTroop() override = default;

    // Getters
    /**
     * @brief Get troop's movement speed
     * @return Current speed value
     */
    [[nodiscard]] inline size_t
    get_speed() const noexcept {
        return speed;
    }

    [[nodiscard]] inline size_t
    get_damage() const noexcept {
        return damage;
    }

    [[nodiscard]] inline size_t
    get_range() const noexcept {
        return range;
    }

    [[nodiscard]] inline size_t
    get_type() const noexcept {
        return type;
    }

    [[nodiscard]] inline size_t
    get_remaining_movement() const noexcept {
        return remaining_movement;
    }

    [[nodiscard]] inline size_t
    get_id_summoner() const noexcept {
        return id_summoner_;
    }

    [[nodiscard]] inline size_t
    get_experience() const noexcept {
        return experience;
    }

    // Setters
    inline void
    set_speed(size_t new_speed) noexcept {
        speed = new_speed;
    }

    inline void
    set_damage(size_t new_damage) noexcept {
        damage = new_damage;
    }

    inline void
    set_range(size_t new_range) noexcept {
        range = new_range;
    }

    inline void
    set_id_summoner(size_t id_summoner) noexcept {
        id_summoner_ = id_summoner;
    }

    inline void
    set_type(size_t new_type) noexcept {
        type = new_type;
    }

    // Modifier methods
    /**
     * @brief Modify troop's speed by delta
     * @param delta Amount to change speed by (can be negative)
     */
    inline void
    modify_speed(int delta) noexcept {
        if (delta < 0 && static_cast<size_t>(-delta) > speed) {
            speed = 0;
        } else {
            if (delta < 0 && static_cast<size_t>(-delta) > speed) {
                speed = 0;
            } else {
                speed = static_cast<size_t>(static_cast<int>(speed) + delta);
            }
        }
    }

    inline void
    modify_damage(int delta) noexcept {
        if (delta < 0 && static_cast<size_t>(-delta) > damage) {
            damage = 0;
        } else {
            damage = static_cast<size_t>(static_cast<int>(damage) + delta);
        }
    }

    inline void
    modify_range(int delta) noexcept {
        if (delta < 0 && static_cast<size_t>(-delta) > range) {
            range = 0;
        } else {
            range = static_cast<size_t>(static_cast<int>(range) + delta);
        }
    }

    /**
     * @brief Use some of troop's movement points
     * @param amount Amount of movement points to spend
     */
    inline void
    spend_movement(size_t amount) noexcept {
        remaining_movement = (amount > remaining_movement) ? 0 : remaining_movement - amount;
    }

    /**
     * @brief Reset movement points to maximum
     */
    inline void
    reset_movement() noexcept {
        remaining_movement = speed;
    }
};

#endif // BASE_TROOP_HPP
