#ifndef MAP_MANAGER_HPP
#define MAP_MANAGER_HPP

#include <future>
#include <memory>
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

/**
 * @brief Manager class for handling the game map and entity positions
 * 
 * Singleton class that manages the game map, including entity positions,
 * cell effects, and movement validation.
 */
class MapManager : public Map {
  private:
    static MapManager* instance_;
    MapManager() = default; // Private constructor

    // Change from raw pointers to shared_ptr
    std::vector<std::shared_ptr<Cell>> effect_cells_;

    /**
     * @brief Processes effects for a range of cells
     * @param start Starting index of the range
     * @param end Ending index of the range
     * @param entity_manager Reference to the EntityManager instance
     */
    void process_effects(size_t start, size_t end, EntityManager& entity_manager);

  public:
    /**
     * @brief Gets the singleton instance of MapManager
     * @return Reference to the MapManager instance
     */
    static MapManager&
    getInstance() {
        if (instance_ == nullptr) {
            instance_ = new MapManager();
        }
        return *instance_;
    }

    /**
     * @brief Destroys the singleton instance
     */
    static void
    destroyInstance() {
        delete instance_;
        instance_ = nullptr;
    }

    EntityList entities_;

    // Add getter for entities_
    [[nodiscard]] const EntityList&
    get_entities() const noexcept {
        return entities_;
    }

    [[nodiscard]] EntityList&
    get_entities() noexcept {
        return entities_;
    }

    MapManager(const MapManager&) = delete;
    MapManager& operator=(const MapManager&) = delete;

    /**
     * @brief Checks if a cell is occupied by an entity
     * @param pos Position to check
     * @return true if cell is occupied, false otherwise
     */
    bool is_cell_occupied(Position pos) const;

    /**
     * @brief Checks if a cell can be passed through
     * @param pos Position to check
     * @return true if cell is passable, false otherwise
     */
    bool is_cell_passable(Position pos) const;

    /**
     * @brief Moves an entity to a new position
     * @param id Entity ID
     * @param delta New position
     * @throws EntityNotFoundException if entity not found
     * @throws CellNotPassableException if target cell is not passable
     * @throws CellOccupiedException if target cell is occupied
     */
    void move_entity(size_t id, Position delta); // Changed return type to void

    /**
     * @brief Processes effects on all effect cells
     */
    void effect_cells();

    bool can_move_entity(size_t id, Position delta) const;
    bool can_entity_act(size_t id, Position delta) const;
    bool add_entity(size_t id, Position pos);
    void remove_entity(size_t id); // Add this line
    std::optional<Position> get_entity_position(size_t id) const;
    void change_cell_type(Position pos, EffectType type, int effect_value = 0, size_t duration = 0);
    bool can_entity_attack(size_t id, Position delta) const;
    const std::vector<std::shared_ptr<Cell>>& get_effect_cells() const;
};

#endif // MAP_MANAGER_HPP
