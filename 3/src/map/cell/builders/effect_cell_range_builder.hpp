#ifndef EFFECT_CELL_RANGE_BUILDER_HPP
#define EFFECT_CELL_RANGE_BUILDER_HPP

#include "map/cell/effect_cell/effect_cell_range.hpp"

class EffectCellRangeBuilder {
  private:
    EffectCellRange cell;

  public:
    EffectCellRangeBuilder(size_t id, Position pos) : cell(id, pos) {}

    EffectCellRangeBuilder&
    set_effect(int range, size_t time) {
        cell.delta_range = range;
        cell.time = time;
        return *this;
    }

    EffectCellRangeBuilder&
    set_passability(bool passability) {
        cell.passability = passability;
        return *this;
    }

    EffectCellRangeBuilder&
    set_busy(bool busy) {
        cell.busy = busy;
        return *this;
    }

    EffectCellRangeBuilder&
    set_id_entity(size_t id_entity) {
        cell.id_entity = id_entity;
        return *this;
    }

    [[nodiscard]] EffectCellRange
    build() const {
        return cell;
    }
};

#endif // EFFECT_CELL_RANGE_BUILDER_HPP
