#ifndef DAMAGE_MANAGER_HPP
#define DAMAGE_MANAGER_HPP

#include "../queue/entity/entity.hpp"
#include "../queue/entity/troop/base_troop.hpp"

class DamageManager {
public:
    void fight(BaseTroop& attacker, Entity& defender);
};

#endif // DAMAGE_MANAGER_HPP