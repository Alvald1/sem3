#ifndef CELL_DIRECTOR_HPP
#define CELL_DIRECTOR_HPP

#include "cell_builder.hpp"
#include "effect_cell_damage_builder.hpp"
#include "effect_cell_hp_builder.hpp"
#include "effect_cell_range_builder.hpp"
#include "effect_cell_speed_builder.hpp"

/**
 * @brief Director class for creating different types of cells
 * 
 * This class provides static methods to create various types of cells
 * using the appropriate builders.
 */
class CellDirector {
  public:
    /**
     * @brief Create a basic cell with specified properties
     * @param pos Position of the cell
     * @param passability Whether the cell is passable (default: true)
     * @return Basic Cell object
     */
    static Cell
    createBasicCell(Position pos, bool passability = true) {
        return CellBuilder(pos).set_passability(passability).set_busy(false).build();
    }

    /**
     * @brief Create a speed effect cell
     * @param pos Position of the cell
     * @param speed Speed modifier value
     * @param duration Duration of the effect
     * @return EffectCellSpeed object
     */
    static EffectCellSpeed
    createSpeedCell(Position pos, int speed, size_t duration) {
        return EffectCellSpeedBuilder(pos).set_effect(speed, duration).set_passability(true).set_busy(false).build();
    }

    /**
     * @brief Create a range effect cell
     * @param pos Position of the cell
     * @param range Range modifier value
     * @param duration Duration of the effect
     * @return EffectCellRange object
     */
    static EffectCellRange
    createRangeCell(Position pos, int range, size_t duration) {
        return EffectCellRangeBuilder(pos).set_effect(range, duration).set_passability(true).set_busy(false).build();
    }

    /**
     * @brief Create an HP effect cell
     * @param pos Position of the cell
     * @param hp HP modifier value
     * @param duration Duration of the effect
     * @return EffectCellHP object
     */
    static EffectCellHP
    createHPCell(Position pos, int hp, size_t duration) {
        return EffectCellHPBuilder(pos).set_effect(hp, duration).set_passability(true).set_busy(false).build();
    }

    /**
     * @brief Create a damage effect cell
     * @param pos Position of the cell
     * @param damage Damage modifier value
     * @param duration Duration of the effect
     * @return EffectCellDamage object
     */
    static EffectCellDamage
    createDamageCell(Position pos, int damage, size_t duration) {
        return EffectCellDamageBuilder(pos).set_effect(damage, duration).set_passability(true).set_busy(false).build();
    }

    /**
     * @brief Create a wall cell (impassable)
     * @param pos Position of the wall
     * @return Cell object configured as a wall
     */
    static Cell
    createWall(Position pos) {
        return CellBuilder(pos).set_passability(false).set_busy(true).build();
    }
};

#endif // CELL_DIRECTOR_HPP
