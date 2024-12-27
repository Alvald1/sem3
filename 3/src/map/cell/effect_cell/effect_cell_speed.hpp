#ifndef EFFECT_CELL_SPEED_HPP
#define EFFECT_CELL_SPEED_HPP

#include "i_effect_cell.hpp"
#include "map/cell/cell.hpp"
#include "map/cell/time.hpp"
#include "utilities/exceptions.hpp"

class EffectCellSpeedBuilder;

class EffectCellSpeed : public Time, public Cell, public IEffectCell {
  private:
    int delta_speed;
    friend class EffectCellSpeedBuilder;

    EffectCellSpeed(Position pos, int speed = 0, bool passability = true, bool busy = false, size_t id_entity = 0,
                    size_t time = 0)
        : Time(time), Cell(pos, passability, busy, id_entity), delta_speed(speed) {}

  public:
    int
    give_effect() override {
        if (is_not_zero()) {
            decrease_time();
            return delta_speed;
        }
        throw EffectExpiredException();
    }

    void
    set_effect(int new_delta_speed, size_t time) override {
        set_time(time);
        delta_speed = new_delta_speed;
    }

    bool
    get_sing() {
        if (delta_speed > 0) {
            return true;
        } else {
            return false;
        }
    }
};

#endif // EFFECT_CELL_SPEED_HPP