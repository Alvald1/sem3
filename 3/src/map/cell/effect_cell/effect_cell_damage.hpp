#ifndef EFFECT_CELL_DAMAGE_HPP
#define EFFECT_CELL_DAMAGE_HPP

#include "i_effect_cell.hpp"
#include "map/cell/cell.hpp"
#include "map/cell/time.hpp"

class EffectCellDamageBuilder;

class EffectCellDamage : public Time, public Cell, public IEffectCell {
  private:
    int delta_damage;
    friend class EffectCellDamageBuilder;

    EffectCellDamage(size_t id, Position pos, int damage = 0, bool passability = true, bool busy = false,
                     size_t id_entity = 0, size_t time = 0)
        : Time(time), Cell(id, pos, passability, busy, id_entity), delta_damage(damage) {}

  public:
    int
    give_effect() override {
        if (is_not_zero()) {
            return delta_damage;
        } else {
            return 0;
        }
    }

    void
    set_effect(int new_delta_damage, size_t time) override {
        set_time(time);
        delta_damage = new_delta_damage;
    }
};

#endif // EFFECT_CELL_DAMAGE_HPP