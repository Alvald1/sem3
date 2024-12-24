#ifndef BASE_TROOP_HPP
#define BASE_TROOP_HPP

#include "queue/entity/entity.hpp"

class BaseTroop : public Entity {

  private:
    size_t speed;
    size_t damage;
    size_t range;
    size_t type;

  protected:
    explicit BaseTroop(const Ability& ability)
        : Entity(ability), speed(ability.get_creature().get_speed()), damage(ability.get_creature().get_damage()),
          range(ability.get_creature().get_range()), type(ability.get_creature().get_type()) {}

  public:
    // Rule of five
    BaseTroop(const BaseTroop&) = default;
    BaseTroop& operator=(const BaseTroop&) = default;
    BaseTroop(BaseTroop&&) noexcept = default;
    BaseTroop& operator=(BaseTroop&&) noexcept = default;
    ~BaseTroop() override = default;

    // Getters
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
    set_type(size_t new_type) noexcept {
        type = new_type;
    }

    // Modifier methods
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
};

#endif // BASE_TROOP_HPP
