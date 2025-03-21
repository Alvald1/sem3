#ifndef EFFECT_CELL_RANGE_HPP
#define EFFECT_CELL_RANGE_HPP

#include "i_effect_cell.hpp"
#include "map/cell/cell.hpp"
#include "map/cell/time.hpp"
#include "utilities/exceptions.hpp"

class EffectCellRangeBuilder;

class EffectCellRange : public Time, public Cell, public IEffectCell {
  private:
    int delta_range;
    friend class EffectCellRangeBuilder;

    EffectCellRange(Position pos, int range = 0, bool passability = true, bool busy = false, size_t id_entity = 0,
                    size_t time = 0)
        : Time(time), Cell(pos, passability, busy, id_entity), delta_range(range) {}

  public:
    int
    give_effect() override {
        if (is_not_zero()) {
            decrease_time();
            return delta_range;
        }
        throw EffectExpiredException();
    }

    void
    set_effect(int new_delta_range, size_t time) override {
        set_time(time);
        delta_range = new_delta_range;
    }

    bool
    get_sing() {
        if (delta_range > 0) {
            return true;
        } else {
            return false;
        }
    }
};

#endif // EFFECT_CELL_RANGE_HPP
