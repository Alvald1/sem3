
#ifndef EFFECT_CELL_HP_HPP
#define EFFECT_CELL_HP_HPP

#include "../cell.hpp"
#include "../time.hpp"
#include "i_effect_cell.hpp"

class EffectCellHP : public Time, public Cell, public IEffectCell {
  private:
    int delta_hp;

  public:
    EffectCellHP() : delta_hp(0) {}

    void
    give_effect(EntityID entity_id) override {
        // Implementation will be added later
    }

    int
    get_delta_hp() const {
        return delta_hp;
    }

    void
    set_delta_hp(int new_delta_hp) {
        delta_hp = new_delta_hp;
    }
};

#endif // EFFECT_CELL_HP_HPP