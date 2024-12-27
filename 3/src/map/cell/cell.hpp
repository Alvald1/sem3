#ifndef CELL_HPP
#define CELL_HPP

#include <cstddef>
#include "utilities/position.hpp"

class CellBuilder;
class EffectCellSpeedBuilder;
class EffectCellRangeBuilder;
class EffectCellHPBuilder;
class EffectCellDamageBuilder;

/**
 * @brief Base class for all cells in the game map
 * 
 * Represents a single cell in the game grid with properties like position,
 * passability, and occupancy status.
 */
class Cell {
  private:
    size_t id;             ///< Unique identifier for the cell
    Position position;     ///< Cell's position in the grid
    bool passability;      ///< Whether entities can pass through this cell
    bool busy;             ///< Whether the cell is currently occupied
    size_t id_entity;      ///< ID of the entity occupying the cell
    static size_t next_id; ///< Counter for generating unique IDs

    friend class CellBuilder;
    friend class EffectCellSpeedBuilder;
    friend class EffectCellRangeBuilder;
    friend class EffectCellHPBuilder;
    friend class EffectCellDamageBuilder;

  protected:
    /**
     * @brief Protected constructor for Cell
     * @param position Cell's position
     * @param passability Whether the cell is passable
     * @param busy Whether the cell is occupied
     * @param id_entity ID of occupying entity
     */
    Cell(Position position, bool passability = true, bool busy = false, size_t id_entity = 0)
        : position(position), passability(passability), busy(busy), id_entity(id_entity) {
        id = next_id++;
    }

  public:
    /**
     * @brief Copy constructor
     * @param other Another Cell object to copy from
     */
    Cell(const Cell& other)
        : id(other.id), position(other.position), passability(other.passability), busy(other.busy),
          id_entity(other.id_entity) {}

    /**
     * @brief Move constructor
     * @param other Another Cell object to move from
     */
    Cell(Cell&& other) noexcept
        : id(other.id), position(std::move(other.position)), passability(other.passability), busy(other.busy),
          id_entity(other.id_entity) {}

    /**
     * @brief Copy assignment operator
     * @param other Another Cell object to copy from
     * @return Reference to this Cell object
     */
    Cell&
    operator=(const Cell& other) {
        if (this != &other) {
            id = other.id;
            position = other.position;
            passability = other.passability;
            busy = other.busy;
            id_entity = other.id_entity;
        }
        return *this;
    }

    /**
     * @brief Move assignment operator
     * @param other Another Cell object to move from
     * @return Reference to this Cell object
     */
    Cell&
    operator=(Cell&& other) noexcept {
        if (this != &other) {
            id = other.id;
            position = std::move(other.position);
            passability = other.passability;
            busy = other.busy;
            id_entity = other.id_entity;
        }
        return *this;
    }

    /**
     * @brief Virtual destructor
     * 
     * Ensures derived classes are properly destructed.
     */
    virtual ~Cell() = default;

    /**
     * @brief Get the cell's position
     * @return Position of the cell
     */
    inline Position
    get_position() const {
        return position;
    }

    /**
     * @brief Check if the cell is passable
     * @return True if the cell is passable, false otherwise
     */
    inline bool
    get_passability() const {
        return passability;
    }

    /**
     * @brief Check if the cell is occupied
     * @return True if the cell is occupied, false otherwise
     */
    inline bool
    get_busy() const {
        return busy;
    }

    /**
     * @brief Get the ID of the entity occupying the cell
     * @return ID of the occupying entity
     */
    inline size_t
    get_id_entity() const {
        return id_entity;
    }

    /**
     * @brief Get the unique ID of the cell
     * @return Unique ID of the cell
     */
    inline size_t
    get_id() const {
        return id;
    }

    /**
     * @brief Set the passability of the cell
     * @param value True if the cell should be passable, false otherwise
     */
    inline void
    set_passability(bool value) {
        passability = value;
    }

    /**
     * @brief Set the occupancy status of the cell
     * @param value True if the cell should be occupied, false otherwise
     */
    inline void
    set_busy(bool value) {
        busy = value;
    }

    /**
     * @brief Set the ID of the entity occupying the cell
     * @param value ID of the occupying entity
     */
    inline void
    set_id_entity(size_t value) {
        id_entity = value;
    }

    /**
     * @brief Check if the cell is empty
     * @return True if the cell is not occupied, false otherwise
     */
    inline bool
    is_empty() const {
        return !busy;
    }
};

#endif // CELL_HPP
