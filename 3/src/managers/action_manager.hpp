#ifndef ACTION_MANAGER_HPP
#define ACTION_MANAGER_HPP

#include <tuple>
#include <vector>
#include "../queue/entity/entity.hpp"
#include "../queue/entity/summoner.hpp"
#include "../queue/entity/troop/base_troop.hpp"
#include "../schools/school/ability/ability.hpp"
#include "../ui/control.hpp"
#include "../utilities/position.hpp"

class ActionManager {
  private:
    static ActionManager* instance_;
    ActionManager() = default;

    using SummonerAction = Control::SummonerAction;

    void handle_summoner_action(Summoner* summoner);
    void handle_troop_action(BaseTroop* troop);

  public:
    static ActionManager&
    getInstance() {
        if (instance_ == nullptr) {
            instance_ = new ActionManager();
        }
        return *instance_;
    }

    ActionManager(const ActionManager&) = delete;
    ActionManager& operator=(const ActionManager&) = delete;

    std::tuple<Position, Position, int> request(Entity& entity);
    Ability choose_ability(bool type, std::vector<Ability>& abilities);

    void
    action(Entity& entity) {
        if (auto* summoner = dynamic_cast<Summoner*>(&entity)) {
            handle_summoner_action(summoner);
        } else if (auto* troop = dynamic_cast<BaseTroop*>(&entity)) {
            handle_troop_action(troop);
        }
    }
};

#endif // ACTION_MANAGER_HPP
