#ifndef EFFECT_CELL_RANGE_HPP
#define EFFECT_CELL_RANGE_HPP

#include "../cell.hpp"
#include "../time.hpp"
#include "i_effect_cell.hpp"

class EffectCellRange : public Time, public Cell, public IEffectCell {
  private:
    int delta_range;

  public:
    EffectCellRange() : delta_range(0) {}

    // Implement pure virtual method from IEffectCell
    void
    give_effect(EntityID entity_id) override {
        // Implementation will be added later
    }

    // Getter and setter for delta_range
    int
    get_delta_range() const {
        return delta_range;
    }

    void
    set_delta_range(int new_delta_range) {
        delta_range = new_delta_range;
    }
};

#endif // EFFECT_CELL_RANGE_HPP
