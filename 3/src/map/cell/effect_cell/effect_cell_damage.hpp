
#ifndef EFFECT_CELL_DAMAGE_HPP
#define EFFECT_CELL_DAMAGE_HPP

#include "../cell.hpp"
#include "../time.hpp"
#include "i_effect_cell.hpp"

class EffectCellDamage : public Time, public Cell, public IEffectCell {
  private:
    int delta_damage;

  public:
    EffectCellDamage() : delta_damage(0) {}

    void
    give_effect(EntityID entity_id) override {
        // Implementation will be added later
    }

    int
    get_delta_damage() const {
        return delta_damage;
    }

    void
    set_delta_damage(int new_delta_damage) {
        delta_damage = new_delta_damage;
    }
};

#endif // EFFECT_CELL_DAMAGE_HPP