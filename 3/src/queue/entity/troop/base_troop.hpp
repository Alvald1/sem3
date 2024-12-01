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
    size_t getSpeed() const { return speed; }
    size_t getDamage() const { return damage; }
    size_t getRange() const { return range; }
    size_t getType() const { return type; }

    // Setters
    void setSpeed(size_t newSpeed) { speed = newSpeed; }
    void setDamage(size_t newDamage) { damage = newDamage; }
    void setRange(size_t newRange) { range = newRange; }
    void setType(size_t newType) { type = newType; }
};

#endif // BASE_TROOP_HPP
