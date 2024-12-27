#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <algorithm>
#include <type_traits>

#include "schools/school/ability/ability.hpp"
#include "utilities/name_id.hpp"

/**
 * @brief Base class for all entities in the game
 * 
 * Represents a basic game entity with health, initiative and identification.
 * Provides core functionality for health management and status checks.
 */
class Entity : public NameID {

  private:
    static inline size_t next_id{1};
    size_t initiative;
    size_t max_hp;
    size_t hp;

  protected:
    /**
     * @brief Construct a new Entity
     * @param ability The ability that defines entity's base stats
     */
    explicit Entity(const Ability& ability) noexcept
        : NameID(next_id++, ability.get_name()), initiative(ability.get_creature().get_initiative()),
          max_hp(ability.get_hp()), hp(ability.get_hp()) {}

  public:
    // Rule of five
    Entity(const Entity&) = default;
    Entity& operator=(const Entity&) = default; // Due to const members
    Entity(Entity&&) noexcept = default;
    Entity& operator=(Entity&&) = default; // Due to const members
    virtual ~Entity() = 0;

    /**
     * @brief Get entity's initiative value
     * @return Current initiative value
     */
    [[nodiscard]] inline size_t
    get_initiative() const noexcept {
        return initiative;
    }

    /**
     * @brief Get entity's current health points
     * @return Current HP value
     */
    [[nodiscard]] inline size_t
    get_hp() const noexcept {
        return hp;
    }

    /**
     * @brief Set entity's current health points
     * @param new_hp New HP value (will be clamped between 0 and max_hp)
     */
    inline void
    set_hp(size_t new_hp) noexcept {
        hp = std::clamp(new_hp, size_t{0}, max_hp);
    }

    /**
     * @brief Get entity's maximum health points
     * @return Maximum HP value
     */
    [[nodiscard]] inline size_t
    get_max_hp() const noexcept {
        return max_hp;
    }

    /**
     * @brief Modify entity's health points by delta
     * @param delta Amount to change HP by (can be negative)
     */
    void
    modify_hp(int delta) noexcept {
        if (delta < 0 && static_cast<size_t>(-delta) > hp) {
            hp = 0;
        } else {
            hp = std::clamp(static_cast<size_t>(static_cast<int>(hp) + delta), size_t{0}, max_hp);
        }
    }

    /**
     * @brief Get entity's health as percentage of maximum
     * @return Health percentage (0-100)
     */
    [[nodiscard]] inline double
    get_health_percentage() const noexcept {
        return (static_cast<double>(hp) / max_hp) * 100.0;
    }

    /**
     * @brief Check if entity is alive
     * @return true if HP > 0, false otherwise
     */
    [[nodiscard]] inline bool
    is_alive() const noexcept {
        return hp > 0;
    }
};

// Need to provide implementation for pure virtual destructor
inline Entity::~Entity() = default;

#endif // ENTITY_HPP
