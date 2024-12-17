#ifndef EFFECT_CELL_HP_HPP
#define EFFECT_CELL_HP_HPP

#include "../cell.hpp"
#include "../time.hpp"
#include "i_effect_cell.hpp"

class EffectCellHP : public Time, public Cell, public IEffectCell {
  private:
    int delta_hp;

  public:
    EffectCellHP(size_t id, Position pos, int hp = 0, bool passability = true, bool busy = false, size_t id_entity = 0,
                 size_t time = 0)
        : Time(time), Cell(id, pos, passability, busy, id_entity), delta_hp(hp) {}

    int
    give_effect() override {
        if (is_not_zero()) {
            return delta_hp;
        } else {
            return 0;
        }
    }

    void
    set_effect(int new_delta_hp, size_t time) override {
        set_time(time);
        delta_hp = new_delta_hp;
    }
};

#endif // EFFECT_CELL_HP_HPP