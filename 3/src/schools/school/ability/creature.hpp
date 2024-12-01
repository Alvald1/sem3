#ifndef CREATURE_HPP
#define CREATURE_HPP

#include "../../../utilities/name_id.hpp"

class Creature : public NameID {
private:
    size_t speed;
    size_t damage;
    size_t range;
    size_t type;
    size_t initiative;

public:
    Creature(size_t id, const std::string& name, size_t speed = 0, size_t damage = 0,
            size_t range = 0, size_t type = 0, size_t initiative = 0)
        : NameID(id, name), speed(speed), damage(damage), 
          range(range), type(type), initiative(initiative) {}

    // Getters
    size_t getSpeed() const { return speed; }
    size_t getDamage() const { return damage; }
    size_t getRange() const { return range; }
    size_t getType() const { return type; }
    size_t getInitiative() const { return initiative; }

    // Setters
    void setSpeed(size_t newSpeed) { speed = newSpeed; }
    void setDamage(size_t newDamage) { damage = newDamage; }
    void setRange(size_t newRange) { range = newRange; }
    void setType(size_t newType) { type = newType; }
    void setInitiative(size_t newInitiative) { initiative = newInitiative; }
};

#endif // CREATURE_HPP
