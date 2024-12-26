#ifndef DAMAGE_MANAGER_HPP
#define DAMAGE_MANAGER_HPP

#include "queue/entity/entity.hpp"
#include "queue/entity/troop/base_troop.hpp"

class DamageManager {
  private:
    static DamageManager* instance_;
    DamageManager() = default;

  public:
    static DamageManager&
    getInstance() {
        if (instance_ == nullptr) {
            instance_ = new DamageManager();
        }
        return *instance_;
    }

    static void
    destroyInstance() {
        delete instance_;
        instance_ = nullptr;
    }

    DamageManager(const DamageManager&) = delete;
    DamageManager& operator=(const DamageManager&) = delete;

    void fight(BaseTroop& attacker, Entity& defender);
};

#endif // DAMAGE_MANAGER_HPP