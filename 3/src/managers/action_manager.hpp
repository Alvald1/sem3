#ifndef ACTION_MANAGER_HPP
#define ACTION_MANAGER_HPP

#include <tuple>
#include <vector>
#include "queue/entity/entity.hpp"
#include "schools/school/ability/ability.hpp"
#include "utilities/position.hpp"

class action_manager {
public:
    std::tuple<Position, Position, int> request(entity& entity);
    ability choose_ability(bool type, std::vector<ability>& abilities);
};

#endif // ACTION_MANAGER_HPP
