#ifndef MAP_MANAGER_HPP
#define MAP_MANAGER_HPP

#include <vector>
#include "../map/cell/cell.hpp"
#include "../map/cell/effect_cell/effect_cell_hp.hpp"
#include "../map/cell/effect_cell/effect_cell_speed.hpp"
#include "../map/cell/effect_cell/effect_cell_range.hpp"
#include "../map/cell/effect_cell/effect_cell_damage.hpp"
#include "../map/entity_list.hpp"
#include "../map/map.hpp"
#include "../utilities/position.hpp"
#include "entity_manager.hpp"

class MapManager : public Map {
  private:
    static MapManager* instance_;
    MapManager() = default;  // Private constructor
    
    EntityList entities_;
    std::vector<Cell*> effect_cells_;
    bool is_cell_occupied(Position pos) const;
    bool is_cell_passable(Position pos) const;

  public:
    static MapManager& getInstance() {
        if (instance_ == nullptr) {
            instance_ = new MapManager();
        }
        return *instance_;
    }

    MapManager(const MapManager&) = delete;
    MapManager& operator=(const MapManager&) = delete;

    enum class MoveResult { SUCCESS, ENTITY_NOT_FOUND, OUT_OF_BOUNDS, CELL_NOT_PASSABLE, CELL_OCCUPIED };

    MoveResult move_entity(size_t id, Position delta);
    void effect_cells();
    bool can_move_entity(size_t id, Position delta) const;
    bool can_entity_act(size_t id, Position delta) const;
};

#endif // MAP_MANAGER_HPP
