#ifndef EFFECT_CELL_SPEED_BUILDER_HPP
#define EFFECT_CELL_SPEED_BUILDER_HPP

#include "map/cell/effect_cell/effect_cell_speed.hpp"

/**
 * @brief Builder class for creating EffectCellSpeed objects
 * 
 * This class implements the Builder pattern for constructing EffectCellSpeed
 * objects with specific attributes.
 */
class EffectCellSpeedBuilder {
  private:
    EffectCellSpeed cell;

  public:
    /**
     * @brief Construct a new Effect Cell Speed Builder object
     * @param pos Initial position for the effect cell
     */
    EffectCellSpeedBuilder(Position pos) : cell(pos) {}

    /**
     * @brief Set the speed effect parameters
     * @param speed Speed modifier value
     * @param time Duration of the effect
     * @return Reference to this builder for method chaining
     */
    EffectCellSpeedBuilder&
    set_effect(int speed, size_t time) {
        cell.delta_speed = speed;
        cell.time = time;
        return *this;
    }

    /**
     * @brief Set the passability of the effect cell
     * @param passability True if the cell is passable, false otherwise
     * @return Reference to this builder for method chaining
     */
    EffectCellSpeedBuilder&
    set_passability(bool passability) {
        cell.passability = passability;
        return *this;
    }

    /**
     * @brief Set whether the effect cell is busy
     * @param busy True if the cell is occupied, false otherwise
     * @return Reference to this builder for method chaining
     */
    EffectCellSpeedBuilder&
    set_busy(bool busy) {
        cell.busy = busy;
        return *this;
    }

    /**
     * @brief Set the entity ID for the effect cell
     * @param id_entity ID of the entity occupying the cell
     * @return Reference to this builder for method chaining
     */
    EffectCellSpeedBuilder&
    set_id_entity(size_t id_entity) {
        cell.id_entity = id_entity;
        return *this;
    }

    /**
     * @brief Build and return the configured EffectCellSpeed object
     * @return EffectCellSpeed object with the configured attributes
     */
    [[nodiscard]] EffectCellSpeed
    build() const {
        return cell;
    }
};

#endif // EFFECT_CELL_SPEED_BUILDER_HPP
