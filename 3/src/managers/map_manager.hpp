#ifndef MAP_MANAGER_HPP
#define MAP_MANAGER_HPP

#include <vector>
#include "../map/cell/cell.hpp"
#include "../queue/entity/entity.hpp"
#include "../map/entity_list.hpp"
#include "../map/map.hpp"
#include "../utilities/position.hpp"

class MapManager : public Map {
private:
    entity_list entities_;
    std::vector<cell> effect_cells_;

public:
    bool move_entity(entity_id id, position delta);
    entity_id perform_action(entity_id id, position delta_pos, int act, position delta_action);
    std::vector<cell> get_effect_cells();
};

#endif // MAP_MANAGER_HPP
