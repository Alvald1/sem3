#ifndef CREATURE_HPP
#define CREATURE_HPP

#include <string>
#include "utilities/name_id.hpp"

class Creature : public NameID {
  private:
    size_t speed{0};
    size_t damage{0};
    size_t range{0};
    size_t type{0};
    size_t initiative{0};

    static inline size_t next_id{1};

  public:
    explicit Creature(std::string name) : NameID(next_id++, std::move(name)) {}

    // Rule of five
    Creature(const Creature&) = default;
    Creature& operator=(const Creature&) = default;
    Creature(Creature&&) noexcept = default;
    Creature& operator=(Creature&&) noexcept = default;
    ~Creature() = default;

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

    [[nodiscard]] inline size_t
    get_initiative() const noexcept {
        return initiative;
    }

    // Add comparison operator
    bool
    operator<(const Creature& other) const {
        return get_id() < other.get_id();
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

    inline void
    set_initiative(size_t new_initiative) noexcept {
        initiative = new_initiative;
    }
};

#endif // CREATURE_HPP
