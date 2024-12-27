#ifndef ACTION_MANAGER_HPP
#define ACTION_MANAGER_HPP

#include <tuple>
#include <vector>

#include "queue/entity/entity.hpp"
#include "queue/entity/summoner.hpp"
#include "queue/entity/troop/base_troop.hpp"
#include "schools/school/ability/ability.hpp"
#include "ui/control.hpp"
#include "utilities/position.hpp"

/**
 * @brief Manages entity actions and their execution
 *
 * This singleton class handles all game actions performed by entities,
 * including movement, combat, summoning, and special abilities.
 */
class ActionManager {
  private:
    static ActionManager* instance_;
    ActionManager() = default;

    using SummonerAction = Control::SummonerAction;

    /**
     * @brief Handle actions specific to summoner entities
     * @param summoner The summoner performing the action
     */
    void handle_summoner_action(Summoner& summoner);

    /**
     * @brief Handle actions specific to troop entities
     * @param troop The troop performing the action
     */
    void handle_troop_action(BaseTroop& troop);

  public:
    /**
     * @brief Get the singleton instance
     * @return Reference to the ActionManager instance
     */
    static ActionManager&
    getInstance() {
        if (instance_ == nullptr) {
            instance_ = new ActionManager();
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

    ActionManager(const ActionManager&) = delete;
    ActionManager& operator=(const ActionManager&) = delete;

    /**
     * @brief Process an entity's action
     * @param entity The entity performing the action
     */
    void
    action(Entity& entity) {
        if (auto* summoner = dynamic_cast<Summoner*>(&entity)) {
            handle_summoner_action(*summoner);
        } else if (auto* troop = dynamic_cast<BaseTroop*>(&entity)) {
            handle_troop_action(*troop);
        }
    }
};

#endif // ACTION_MANAGER_HPP
