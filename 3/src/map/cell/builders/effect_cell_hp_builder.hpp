#ifndef EFFECT_CELL_HP_BUILDER_HPP
#define EFFECT_CELL_HP_BUILDER_HPP

#include "map/cell/effect_cell/effect_cell_hp.hpp"

class EffectCellHPBuilder {
  private:
    EffectCellHP cell;

  public:
    EffectCellHPBuilder(Position pos) : cell(pos) {}

    EffectCellHPBuilder&
    set_effect(int hp, size_t time) {
        cell.delta_hp = hp;
        cell.time = time;
        return *this;
    }

    EffectCellHPBuilder&
    set_passability(bool passability) {
        cell.passability = passability;
        return *this;
    }

    EffectCellHPBuilder&
    set_busy(bool busy) {
        cell.busy = busy;
        return *this;
    }

    EffectCellHPBuilder&
    set_id_entity(size_t id_entity) {
        cell.id_entity = id_entity;
        return *this;
    }

    [[nodiscard]] EffectCellHP
    build() const {
        return cell;
    }
};

#endif // EFFECT_CELL_HP_BUILDER_HPP
