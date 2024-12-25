#ifndef EFFECT_CELL_SPEED_BUILDER_HPP
#define EFFECT_CELL_SPEED_BUILDER_HPP

#include "map/cell/effect_cell/effect_cell_speed.hpp"

class EffectCellSpeedBuilder {
  private:
    EffectCellSpeed cell;

  public:
    EffectCellSpeedBuilder(size_t id, Position pos) : cell(id, pos) {}

    EffectCellSpeedBuilder&
    set_effect(int speed, size_t time) {
        cell.delta_speed = speed;
        cell.time = time;
        return *this;
    }

    EffectCellSpeedBuilder&
    set_passability(bool passability) {
        cell.passability = passability;
        return *this;
    }

    EffectCellSpeedBuilder&
    set_busy(bool busy) {
        cell.busy = busy;
        return *this;
    }

    EffectCellSpeedBuilder&
    set_id_entity(size_t id_entity) {
        cell.id_entity = id_entity;
        return *this;
    }

    [[nodiscard]] EffectCellSpeed
    build() const {
        return cell;
    }
};

#endif // EFFECT_CELL_SPEED_BUILDER_HPP
