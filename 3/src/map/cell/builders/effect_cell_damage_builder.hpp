#ifndef EFFECT_CELL_DAMAGE_BUILDER_HPP
#define EFFECT_CELL_DAMAGE_BUILDER_HPP

#include "map/cell/effect_cell/effect_cell_damage.hpp"

class EffectCellDamageBuilder {
  private:
    EffectCellDamage cell;

  public:
    EffectCellDamageBuilder(Position pos) : cell(pos) {}

    EffectCellDamageBuilder&
    set_effect(int damage, size_t time) {
        cell.delta_damage = damage;
        cell.time = time;
        return *this;
    }

    EffectCellDamageBuilder&
    set_passability(bool passability) {
        cell.passability = passability;
        return *this;
    }

    EffectCellDamageBuilder&
    set_busy(bool busy) {
        cell.busy = busy;
        return *this;
    }

    EffectCellDamageBuilder&
    set_id_entity(size_t id_entity) {
        cell.id_entity = id_entity;
        return *this;
    }

    [[nodiscard]] EffectCellDamage
    build() const {
        return cell;
    }
};

#endif // EFFECT_CELL_DAMAGE_BUILDER_HPP
