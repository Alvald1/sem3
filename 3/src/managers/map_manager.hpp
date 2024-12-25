#ifndef MAP_MANAGER_HPP
#define MAP_MANAGER_HPP

#include <future>
#include <optional>
#include <thread>
#include <vector>

#include "entity_manager.hpp"
#include "map/cell/cell.hpp"
#include "map/cell/effect_cell/effect_cell_damage.hpp"
#include "map/cell/effect_cell/effect_cell_hp.hpp"
#include "map/cell/effect_cell/effect_cell_range.hpp"
#include "map/cell/effect_cell/effect_cell_speed.hpp"
#include "map/entity_list.hpp"
#include "map/map.hpp"
#include "utilities/position.hpp"
#include "utilities/type_system.hpp"

class MapManager : public Map {
  private:
    static MapManager* instance_;
    MapManager() = default; // Private constructor

    EntityList entities_;
    std::vector<Cell*> effect_cells_;

    void process_effects(size_t start, size_t end, EntityManager& entity_manager);

  public:
    static MapManager&
    getInstance() {
        if (instance_ == nullptr) {
            instance_ = new MapManager();
        }
        return *instance_;
    }

    MapManager(const MapManager&) = delete;
    MapManager& operator=(const MapManager&) = delete;

    bool is_cell_occupied(Position pos) const;
    bool is_cell_passable(Position pos) const;
    void move_entity(size_t id, Position delta); // Changed return type to void
    void effect_cells();
    bool can_move_entity(size_t id, Position delta) const;
    bool can_entity_act(size_t id, Position delta) const;
    bool add_entity(size_t id, Position pos);
    std::optional<Position> get_entity_position(size_t id) const;
};

#endif // MAP_MANAGER_HPP
