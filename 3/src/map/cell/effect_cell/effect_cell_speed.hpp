
#ifndef EFFECT_CELL_SPEED_HPP
#define EFFECT_CELL_SPEED_HPP

#include "../cell.hpp"
#include "../time.hpp"
#include "i_effect_cell.hpp"

class EffectCellSpeed : public Time, public Cell, public IEffectCell {
  private:
    int delta_speed;

  public:
    EffectCellSpeed() : delta_speed(0) {}

    void
    give_effect(EntityID entity_id) override {
        // Implementation will be added later
    }

    int
    get_delta_speed() const {
        return delta_speed;
    }

    void
    set_delta_speed(int new_delta_speed) {
        delta_speed = new_delta_speed;
    }
};

#endif // EFFECT_CELL_SPEED_HPP