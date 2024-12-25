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
    createBasicCell(size_t id, Position pos, bool passability = true) {
        return CellBuilder(id, pos).set_passability(passability).set_busy(false).build();
    }

    static EffectCellSpeed
    createSpeedCell(size_t id, Position pos, int speed, size_t duration) {
        return EffectCellSpeedBuilder(id, pos)
            .set_effect(speed, duration)
            .set_passability(true)
            .set_busy(false)
            .build();
    }

    static EffectCellRange
    createRangeCell(size_t id, Position pos, int range, size_t duration) {
        return EffectCellRangeBuilder(id, pos)
            .set_effect(range, duration)
            .set_passability(true)
            .set_busy(false)
            .build();
    }

    static EffectCellHP
    createHPCell(size_t id, Position pos, int hp, size_t duration) {
        return EffectCellHPBuilder(id, pos).set_effect(hp, duration).set_passability(true).set_busy(false).build();
    }

    static EffectCellDamage
    createDamageCell(size_t id, Position pos, int damage, size_t duration) {
        return EffectCellDamageBuilder(id, pos)
            .set_effect(damage, duration)
            .set_passability(true)
            .set_busy(false)
            .build();
    }

    // Create a wall (impassable cell)
    static Cell
    createWall(size_t id, Position pos) {
        return CellBuilder(id, pos).set_passability(false).set_busy(true).build();
    }
};

#endif // CELL_DIRECTOR_HPP
