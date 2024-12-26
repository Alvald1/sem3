#ifndef CELL_DIRECTOR_HPP
#define CELL_DIRECTOR_HPP

#include "cell_builder.hpp"
#include "effect_cell_damage_builder.hpp"
#include "effect_cell_hp_builder.hpp"
#include "effect_cell_range_builder.hpp"
#include "effect_cell_speed_builder.hpp"

class CellDirector {
  public:
    static Cell
    createBasicCell(Position pos, bool passability = true) {
        return CellBuilder(pos).set_passability(passability).set_busy(false).build();
    }

    static EffectCellSpeed
    createSpeedCell(Position pos, int speed, size_t duration) {
        return EffectCellSpeedBuilder(pos).set_effect(speed, duration).set_passability(true).set_busy(false).build();
    }

    static EffectCellRange
    createRangeCell(Position pos, int range, size_t duration) {
        return EffectCellRangeBuilder(pos).set_effect(range, duration).set_passability(true).set_busy(false).build();
    }

    static EffectCellHP
    createHPCell(Position pos, int hp, size_t duration) {
        return EffectCellHPBuilder(pos).set_effect(hp, duration).set_passability(true).set_busy(false).build();
    }

    static EffectCellDamage
    createDamageCell(Position pos, int damage, size_t duration) {
        return EffectCellDamageBuilder(pos).set_effect(damage, duration).set_passability(true).set_busy(false).build();
    }

    // Create a wall (impassable cell)
    static Cell
    createWall(Position pos) {
        return CellBuilder(pos).set_passability(false).set_busy(true).build();
    }
};

#endif // CELL_DIRECTOR_HPP
