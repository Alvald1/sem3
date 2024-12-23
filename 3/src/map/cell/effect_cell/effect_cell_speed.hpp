#ifndef EFFECT_CELL_SPEED_HPP
#define EFFECT_CELL_SPEED_HPP

#include <cstddef>
#include "i_effect_cell.hpp"
#include "map/cell/cell.hpp"
#include "map/cell/time.hpp"

class EffectCellSpeed : public Time, public Cell, public IEffectCell {
  private:
    int delta_speed;

  public:
    EffectCellSpeed(size_t id, Position pos, int speed = 0, bool passability = true, bool busy = false,
                    size_t id_entity = 0, size_t time = 0)
        : Time(time), Cell(id, pos, passability, busy, id_entity), delta_speed(speed) {}

    int
    give_effect() override {
        if (is_not_zero()) {
            return delta_speed;
        } else {
            return 0;
        }
    }

    void
    set_effect(int new_delta_speed, size_t time) override {
        set_time(time);
        delta_speed = new_delta_speed;
    }
};

#endif // EFFECT_CELL_SPEED_HPP