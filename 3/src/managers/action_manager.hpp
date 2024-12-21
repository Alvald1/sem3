#ifndef ACTION_MANAGER_HPP
#define ACTION_MANAGER_HPP

#include <tuple>
#include <vector>
#include "../queue/entity/entity.hpp"
#include "../schools/school/ability/ability.hpp"
#include "../utilities/position.hpp"

class ActionManager {
  public:
    std::tuple<Position, Position, int> request(Entity& entity);
    Ability choose_ability(bool type, std::vector<Ability>& abilities);
};

#endif // ACTION_MANAGER_HPP
