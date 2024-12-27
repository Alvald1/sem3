#ifndef EFFECT_CELL_DAMAGE_HPP
#define EFFECT_CELL_DAMAGE_HPP

#include "i_effect_cell.hpp"
#include "map/cell/cell.hpp"
#include "map/cell/time.hpp"
#include "utilities/exceptions.hpp"

class EffectCellDamageBuilder;

class EffectCellDamage : public Time, public Cell, public IEffectCell {
  private:
    int delta_damage;
    friend class EffectCellDamageBuilder;

    EffectCellDamage(Position pos, int damage = 0, bool passability = true, bool busy = false, size_t id_entity = 0,
                     size_t time = 0)
        : Time(time), Cell(pos, passability, busy, id_entity), delta_damage(damage) {}

  public:
    int
    give_effect() override {
        if (is_not_zero()) {
            decrease_time();
            return delta_damage;
        }
        throw EffectExpiredException();
    }

    void
    set_effect(int new_delta_damage, size_t time) override {
        set_time(time);
        delta_damage = new_delta_damage;
    }

    bool
    get_sing() {
        if (delta_damage > 0) {
            return true;
        } else {
            return false;
        }
    }
};

#endif // EFFECT_CELL_DAMAGE_HPP