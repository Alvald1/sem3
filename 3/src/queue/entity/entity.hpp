#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../../utilities/name_id.hpp"

class Entity : public NameID {
private:
    size_t initiative;
    size_t hp;
    const size_t max_hp;

public:
    Entity(size_t id, const std::string& name, size_t initiative, size_t max_hp)
        : NameID(id, name), initiative(initiative), max_hp(max_hp), hp(max_hp) {}

    size_t getInitiative() const { return initiative; }

    size_t getHp() const { return hp; }
    void setHp(size_t newHp) { hp = std::min(newHp, max_hp); }

    size_t getMaxHp() const { return max_hp; }

    void defence(int deltaHp) {
        if (deltaHp < 0 && static_cast<size_t>(-deltaHp) > hp) {
            hp = 0;
        } else {
            hp = std::min(max_hp, static_cast<size_t>(static_cast<int>(hp) + deltaHp));
        }
    }
};

#endif // ENTITY_HPP
