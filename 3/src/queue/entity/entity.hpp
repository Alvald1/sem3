#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <algorithm>
#include <type_traits>

#include "schools/school/ability/ability.hpp"
#include "utilities/name_id.hpp"

class EntityBuilder; // Forward declaration

class Entity : public NameID {
    friend class EntityBuilder;

  private:
    static inline size_t next_id{1};
    size_t initiative;
    size_t max_hp;
    size_t hp;

  protected:
    explicit Entity(const Ability& ability) noexcept
        : NameID(next_id++, ability.get_name()), initiative(ability.get_creature().get_initiative()),
          max_hp(ability.get_count()), hp(ability.get_count()) {}

  public:
    // Rule of five
    Entity(const Entity&) = default;
    Entity& operator=(const Entity&) = default; // Due to const members
    Entity(Entity&&) noexcept = default;
    Entity& operator=(Entity&&) = default; // Due to const members
    virtual ~Entity() = 0;

    [[nodiscard]] inline size_t
    get_initiative() const noexcept {
        return initiative;
    }

    [[nodiscard]] inline size_t
    get_hp() const noexcept {
        return hp;
    }

    inline void
    set_hp(size_t new_hp) noexcept {
        hp = std::clamp(new_hp, size_t{0}, max_hp);
    }

    [[nodiscard]] inline size_t
    get_max_hp() const noexcept {
        return max_hp;
    }

    void
    modify_hp(int delta) noexcept {
        if (delta < 0 && static_cast<size_t>(-delta) > hp) {
            hp = 0;
        } else {
            hp = std::clamp(static_cast<size_t>(static_cast<int>(hp) + delta), size_t{0}, max_hp);
        }
    }

    [[nodiscard]] inline double
    get_health_percentage() const noexcept {
        return (static_cast<double>(hp) / max_hp) * 100.0;
    }

    [[nodiscard]] inline bool
    is_alive() const noexcept {
        return hp > 0;
    }
};

// Need to provide implementation for pure virtual destructor
inline Entity::~Entity() = default;

#endif // ENTITY_HPP
