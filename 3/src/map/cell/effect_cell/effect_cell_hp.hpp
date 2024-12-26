#ifndef EFFECT_CELL_HP_HPP
#define EFFECT_CELL_HP_HPP

#include "i_effect_cell.hpp"
#include "map/cell/cell.hpp"
#include "map/cell/time.hpp"
#include "utilities/exceptions.hpp"

class EffectCellHPBuilder;

class EffectCellHP : public Time, public Cell, public IEffectCell {
  private:
    int delta_hp;
    friend class EffectCellHPBuilder;

    EffectCellHP(Position pos, int hp = 0, bool passability = true, bool busy = false, size_t id_entity = 0,
                 size_t time = 0)
        : Time(time), Cell(pos, passability, busy, id_entity), delta_hp(hp) {}

  public:
    int
    give_effect() override {
        if (is_not_zero()) {
            decrease_time();
            return delta_hp;
        }
        throw EffectExpiredException();
    }

    void
    set_effect(int new_delta_hp, size_t time) override {
        set_time(time);
        delta_hp = new_delta_hp;
    }
};

#endif // EFFECT_CELL_HP_HPP