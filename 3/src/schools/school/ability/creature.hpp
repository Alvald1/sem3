#ifndef CREATURE_HPP
#define CREATURE_HPP

#include <string>
#include "utilities/name_id.hpp"

class Creature : public NameID {
  private:
    size_t speed_{0};
    size_t damage_{0};
    size_t range_{0};
    size_t type_{0};
    size_t initiative_{0};

    static inline size_t next_id{1};

  public:
    explicit Creature(const std::string& name) : NameID(next_id++, name) {}

    // Rule of five
    Creature(const Creature&) = default;
    Creature& operator=(const Creature&) = default;
    Creature(Creature&&) noexcept = default;
    Creature& operator=(Creature&&) noexcept = default;
    ~Creature() = default;

    // Getters
    [[nodiscard]] inline size_t
    get_speed() const noexcept {
        return speed_;
    }

    [[nodiscard]] inline size_t
    get_damage() const noexcept {
        return damage_;
    }

    [[nodiscard]] inline size_t
    get_range() const noexcept {
        return range_;
    }

    [[nodiscard]] inline size_t
    get_type() const noexcept {
        return type_;
    }

    [[nodiscard]] inline size_t
    get_initiative() const noexcept {
        return initiative_;
    }

    // Add comparison operator
    bool
    operator<(const Creature& other) const {
        return get_id() < other.get_id();
    }

    // Setters
    inline void
    set_speed(size_t new_speed) noexcept {
        speed_ = new_speed;
    }

    inline void
    set_damage(size_t new_damage) noexcept {
        damage_ = new_damage;
    }

    inline void
    set_range(size_t new_range) noexcept {
        range_ = new_range;
    }

    inline void
    set_type(size_t new_type) noexcept {
        type_ = new_type;
    }

    inline void
    set_initiative(size_t new_initiative) noexcept {
        initiative_ = new_initiative;
    }
};

#endif // CREATURE_HPP
