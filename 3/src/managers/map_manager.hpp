#ifndef MAP_MANAGER_HPP
#define MAP_MANAGER_HPP

#include <vector>
#include "../map/cell/cell.hpp"
#include "../map/entity_list.hpp"
#include "../map/map.hpp"
#include "../utilities/position.hpp"

class MapManager : public Map {
  public:
    enum class MoveResult { SUCCESS, ENTITY_NOT_FOUND, OUT_OF_BOUNDS, CELL_NOT_PASSABLE, CELL_OCCUPIED };

  private:
    EntityList entities_;
    std::vector<Cell*> effect_cells_;
    bool is_cell_occupied(Position pos) const;
    bool is_cell_passable(Position pos) const;

  public:
    MoveResult move_entity(size_t id, Position delta);
    std::vector<Cell*> effect_cells();
    bool can_move_entity(size_t id, Position delta) const;
    bool can_entity_act(size_t id, Position delta) const;
};

#endif // MAP_MANAGER_HPP
