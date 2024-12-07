#ifndef CREATURE_HPP
#define CREATURE_HPP

#include "../../../utilities/name_id.hpp"

class Creature : public NameID {
  private:
    size_t speed{0};
    size_t damage{0};
    size_t range{0};
    size_t type{0};
    size_t initiative{0};

    static inline size_t id_counter{0};

  public:
    explicit Creature(std::string name, size_t speed = 0, size_t damage = 0, size_t range = 0, size_t type = 0,
                     size_t initiative = 0)
        : NameID(++id_counter, std::move(name))
        , speed(speed)
        , damage(damage)
        , range(range)
        , type(type)
        , initiative(initiative) {}

    // Rule of five
    Creature(const Creature&) = default;
    Creature& operator=(const Creature&) = default;
    Creature(Creature&&) noexcept = default;
    Creature& operator=(Creature&&) noexcept = default;
    ~Creature() = default;

    // Getters
    [[nodiscard]] constexpr auto
    get_speed() const noexcept {
        return speed;
    }

    [[nodiscard]] constexpr auto
    get_damage() const noexcept {
        return damage;
    }

    [[nodiscard]] constexpr auto
    get_range() const noexcept {
        return range;
    }

    [[nodiscard]] constexpr auto
    get_type() const noexcept {
        return type;
    }

    [[nodiscard]] constexpr auto
    get_initiative() const noexcept {
        return initiative;
    }

    // Setters
    constexpr void
    set_speed(size_t new_speed) noexcept {
        speed = new_speed;
    }

    constexpr void
    set_damage(size_t new_damage) noexcept {
        damage = new_damage;
    }

    constexpr void
    set_range(size_t new_range) noexcept {
        range = new_range;
    }

    constexpr void
    set_type(size_t new_type) noexcept {
        type = new_type;
    }

    constexpr void
    set_initiative(size_t new_initiative) noexcept {
        initiative = new_initiative;
    }
};

#endif // CREATURE_HPP
