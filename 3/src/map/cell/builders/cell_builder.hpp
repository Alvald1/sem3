#ifndef CELL_BUILDER_HPP
#define CELL_BUILDER_HPP

#include "map/cell/cell.hpp"
#include "utilities/position.hpp"

/**
 * @brief Builder class for creating Cell objects
 * 
 * This class implements the Builder pattern for constructing Cell objects
 * with specific attributes.
 */
class CellBuilder {
  protected:
    Cell cell;

  public:
    /**
     * @brief Construct a new Cell Builder object
     * @param pos Initial position for the cell
     */
    CellBuilder(Position pos) : cell(pos) {}

    /**
     * @brief Set the passability of the cell
     * @param passability True if the cell is passable, false otherwise
     * @return Reference to this builder for method chaining
     */
    CellBuilder&
    set_passability(bool passability) {
        cell.passability = passability;
        return *this;
    }

    /**
     * @brief Set whether the cell is busy
     * @param busy True if the cell is occupied, false otherwise
     * @return Reference to this builder for method chaining
     */
    CellBuilder&
    set_busy(bool busy) {
        cell.busy = busy;
        return *this;
    }

    /**
     * @brief Set the entity ID for the cell
     * @param id_entity ID of the entity occupying the cell
     * @return Reference to this builder for method chaining
     */
    CellBuilder&
    set_id_entity(size_t id_entity) {
        cell.id_entity = id_entity;
        return *this;
    }

    /**
     * @brief Build and return the configured Cell object
     * @return Cell object with the configured attributes
     */
    [[nodiscard]] Cell
    build() const {
        return cell;
    }
};

#endif // CELL_BUILDER_HPP
