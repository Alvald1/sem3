#ifndef ACTION_MANAGER_HPP
#define ACTION_MANAGER_HPP

#include <tuple>
#include <vector>
#include "../queue/entity/entity.hpp"
#include "../schools/school/ability/ability.hpp"
#include "../utilities/position.hpp"

class ActionManager {
private:
    static ActionManager* instance_;
    ActionManager() = default;

public:
    static ActionManager& getInstance() {
        if (instance_ == nullptr) {
            instance_ = new ActionManager();
        }
        return *instance_;
    }

    ActionManager(const ActionManager&) = delete;
    ActionManager& operator=(const ActionManager&) = delete;

public:
    std::tuple<Position, Position, int> request(Entity& entity);
    Ability choose_ability(bool type, std::vector<Ability>& abilities);
};

#endif // ACTION_MANAGER_HPP
