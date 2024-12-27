#ifndef CREATURE_HPP
#define CREATURE_HPP

#include <string>
#include "utilities/name_id.hpp"

/**
 * @brief Represents a creature with combat attributes
 * 
 * Each creature has unique attributes like speed, damage, range,
 * type and initiative. Inherits from NameID for identification.
 */
class Creature : public NameID {
  private:
    size_t speed_{0};
    size_t damage_{0};
    size_t range_{0};
    size_t type_{0};
    size_t initiative_{0};

    static inline size_t next_id{1};

  public:
    /**
     * @brief Construct a new Creature
     * @param name Name of the creature
     */
    explicit Creature(const std::string& name) : NameID(next_id++, name) {}

    // Rule of five
    Creature(const Creature&) = default;
    Creature& operator=(const Creature&) = default;
    Creature(Creature&&) noexcept = default;
    Creature& operator=(Creature&&) noexcept = default;
    ~Creature() = default;

    // Getters
    /**
     * @brief Get creature's speed
     * @return Speed value
     */
    [[nodiscard]] inline size_t
    get_speed() const noexcept {
        return speed_;
    }

    /**
     * @brief Get creature's damage
     * @return Damage value
     */
    [[nodiscard]] inline size_t
    get_damage() const noexcept {
        return damage_;
    }

    /**
     * @brief Get creature's range
     * @return Range value
     */
    [[nodiscard]] inline size_t
    get_range() const noexcept {
        return range_;
    }

    /**
     * @brief Get creature's type
     * @return Type value
     */
    [[nodiscard]] inline size_t
    get_type() const noexcept {
        return type_;
    }

    /**
     * @brief Get creature's initiative
     * @return Initiative value
     */
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
    /**
     * @brief Set creature's speed
     * @param new_speed New speed value
     */
    inline void
    set_speed(size_t new_speed) noexcept {
        speed_ = new_speed;
    }

    /**
     * @brief Set creature's damage
     * @param new_damage New damage value
     */
    inline void
    set_damage(size_t new_damage) noexcept {
        damage_ = new_damage;
    }

    /**
     * @brief Set creature's range
     * @param new_range New range value
     */
    inline void
    set_range(size_t new_range) noexcept {
        range_ = new_range;
    }

    /**
     * @brief Set creature's type
     * @param new_type New type value
     */
    inline void
    set_type(size_t new_type) noexcept {
        type_ = new_type;
    }

    /**
     * @brief Set creature's initiative
     * @param new_initiative New initiative value
     */
    inline void
    set_initiative(size_t new_initiative) noexcept {
        initiative_ = new_initiative;
    }
};

#endif // CREATURE_HPP
