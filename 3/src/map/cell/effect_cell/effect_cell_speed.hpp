#ifndef EFFECT_CELL_SPEED_HPP
#define EFFECT_CELL_SPEED_HPP

#include "i_effect_cell.hpp"
#include "map/cell/cell.hpp"
#include "map/cell/time.hpp"
#include "utilities/exceptions.hpp"

class EffectCellSpeedBuilder;

/**
 * @brief Cell that applies speed effects to entities
 * 
 * This class represents a cell that can modify the speed of entities
 * that interact with it. The effect can be positive (speed boost) or
 * negative (speed reduction).
 */
class EffectCellSpeed : public Time, public Cell, public IEffectCell {
  private:
    int delta_speed; ///< Speed modification value
    friend class EffectCellSpeedBuilder;

    /**
     * @brief Private constructor for EffectCellSpeed
     * @param pos Position of the cell
     * @param speed Speed modification value
     * @param passability Whether the cell is passable
     * @param busy Whether the cell is occupied
     * @param id_entity ID of occupying entity
     * @param time Duration of the effect
     */
    EffectCellSpeed(Position pos, int speed = 0, bool passability = true, bool busy = false, size_t id_entity = 0,
                    size_t time = 0)
        : Time(time), Cell(pos, passability, busy, id_entity), delta_speed(speed) {}

  public:
    /**
     * @brief Apply the speed effect
     * @return int Speed modification value
     * @throws EffectExpiredException if the effect has expired
     */
    int
    give_effect() override {
        if (is_not_zero()) {
            decrease_time();
            return delta_speed;
        }
        throw EffectExpiredException();
    }

    /**
     * @brief Set the speed effect parameters
     * @param new_delta_speed New speed modification value
     * @param time Duration of the effect
     */
    void
    set_effect(int new_delta_speed, size_t time) override {
        set_time(time);
        delta_speed = new_delta_speed;
    }

    /**
     * @brief Get the sign of the speed modification
     * @return true if speed boost, false if speed reduction
     */
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