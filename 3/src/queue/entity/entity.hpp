#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../../schools/school/ability/ability.hpp"
#include "../../utilities/name_id.hpp"

class Entity : public NameID {
  private:
    static inline size_t next_id{1};
    size_t initiative;
    size_t hp;
    const size_t max_hp;

  public:
    explicit Entity(const Ability& ability)
        : NameID(next_id++, ability.get_name()), initiative(ability.get_creature()->get_initiative()),
          max_hp(ability.get_count()), hp(max_hp) {}

    virtual ~Entity() = default;

    Entity(const Entity&) = delete;
    Entity& operator=(const Entity&) = delete;

    // Запрещаем перемещение
    Entity(Entity&&) = delete;
    Entity& operator=(Entity&&) = delete;

    size_t
    get_initiative() const {
        return initiative;
    }

    size_t
    get_hp() const {
        return hp;
    }

    void
    set_hp(size_t new_hp) {
        hp = std::min(new_hp, max_hp);
    }

    size_t
    get_max_hp() const {
        return max_hp;
    }

    void
    heal(size_t amount) {

        hp = std::min(hp + amount, max_hp);
    }

    [[nodiscard]] double
    get_health_percentage() const {
        return (static_cast<double>(hp) / max_hp) * 100.0;
    }

    void
    damage(size_t amount) {
        hp = (amount >= hp) ? 0 : hp - amount;
    }

    bool
    is_alive() const {
        return hp > 0;
    }

    bool
    operator<(const Entity& other) const {
        return initiative < other.initiative;
    }

    bool
    operator>(const Entity& other) const {
        return initiative > other.initiative;
    }
};

#endif // ENTITY_HPP
