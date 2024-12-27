#ifndef DAMAGE_MANAGER_HPP
#define DAMAGE_MANAGER_HPP

#include "queue/entity/entity.hpp"
#include "queue/entity/troop/base_troop.hpp"

/**
 * @brief Manages combat and damage calculations between entities
 *
 * This singleton class handles all combat interactions between troops and entities,
 * including damage calculation, counterattacks, and death processing.
 */
class DamageManager {
  private:
    static DamageManager* instance_;
    DamageManager() = default;

  public:
    /**
     * @brief Get the singleton instance
     * @return Reference to the DamageManager instance
     */
    static DamageManager&
    getInstance() {
        if (instance_ == nullptr) {
            instance_ = new DamageManager();
        }
        return *instance_;
    }

    /**
     * @brief Destroy the singleton instance
     */
    static void
    destroyInstance() {
        delete instance_;
        instance_ = nullptr;
    }

    DamageManager(const DamageManager&) = delete;
    DamageManager& operator=(const DamageManager&) = delete;

    /**
     * @brief Process combat between two entities
     * @param attacker The troop initiating the attack
     * @param defender The entity being attacked
     * @throw FriendlyFireException if attacking allied unit
     */
    void fight(BaseTroop& attacker, Entity& defender);
};

#endif // DAMAGE_MANAGER_HPP