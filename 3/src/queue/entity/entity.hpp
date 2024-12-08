#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <algorithm>
#include <type_traits>
#include "../../schools/school/ability/ability.hpp"
#include "../../utilities/name_id.hpp"

class Entity : public NameID {
  private:
    static inline size_t next_id{1};
    size_t initiative;
    size_t hp;
    const size_t max_hp;

  public:
    explicit Entity(const Ability& ability) noexcept
        : NameID(next_id++, ability.get_name()), initiative(ability.get_creature()->get_initiative()),
          max_hp(ability.get_count()), hp(ability.get_count()) {}

    virtual ~Entity() = default;

    // Delete assignment operators since we have const members
    Entity(const Entity&) = default;
    Entity& operator=(const Entity&) = delete;

    Entity(Entity&&) = default;
    Entity& operator=(Entity&&) = delete;

    [[nodiscard]] constexpr size_t
    get_initiative() const noexcept {
        return initiative;
    }

    [[nodiscard]] constexpr size_t
    get_hp() const noexcept {
        return hp;
    }

    constexpr void
    set_hp(size_t new_hp) noexcept {
        hp = std::clamp(new_hp, size_t{0}, max_hp);
    }

    [[nodiscard]] constexpr size_t
    get_max_hp() const noexcept {
        return max_hp;
    }

    constexpr void
    heal(size_t amount) noexcept {
        if (std::make_signed_t<size_t>(amount) < 0) {
            return;
        }
        hp = std::clamp(hp + amount, size_t{0}, max_hp);
    }

    [[nodiscard]] constexpr double
    get_health_percentage() const noexcept {
        return (static_cast<double>(hp) / max_hp) * 100.0;
    }

    constexpr void
    do_damage(size_t amount) noexcept {
        if (std::make_signed_t<size_t>(amount) < 0) {
            return;
        }
        hp = (amount >= hp) ? 0 : hp - amount;
    }

    [[nodiscard]] constexpr bool
    is_alive() const noexcept {
        return hp > 0;
    }

    [[nodiscard]] constexpr bool
    operator<(const Entity& other) const noexcept {
        return initiative < other.initiative;
    }

    [[nodiscard]] constexpr bool
    operator>(const Entity& other) const noexcept {
        return initiative > other.initiative;
    }

    [[nodiscard]] constexpr bool
    operator==(const Entity& other) const noexcept {
        return initiative == other.initiative;
    }

    [[nodiscard]] constexpr bool
    operator<=(const Entity& other) const noexcept {
        return initiative <= other.initiative;
    }

    [[nodiscard]] constexpr bool
    operator>=(const Entity& other) const noexcept {
        return initiative >= other.initiative;
    }
};

#endif // ENTITY_HPP
