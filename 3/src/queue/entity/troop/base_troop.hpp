#ifndef BASE_TROOP_HPP
#define BASE_TROOP_HPP

#include "../../entity.hpp"

class BaseTroop : public Entity {
private:
    size_t speed;
    size_t damage;
    size_t range;
    size_t type;

public:
    BaseTroop(size_t id, const std::string& name, size_t initiative, size_t max_hp,
              size_t speed, size_t damage, size_t range, size_t type)
        : Entity(id, name, initiative, max_hp),
          speed(speed), damage(damage), range(range), type(type) {}

    // Getters
    size_t get_speed() const { return speed; }
    size_t get_damage() const { return damage; }
    size_t get_range() const { return range; }
    size_t get_type() const { return type; }

    // Setters
    void set_speed(size_t new_speed) { speed = new_speed; }
    void set_damage(size_t new_damage) { damage = new_damage; }
    void set_range(size_t new_range) { range = new_range; }
    void set_type(size_t new_type) { type = new_type; }
};

#endif // BASE_TROOP_HPP
