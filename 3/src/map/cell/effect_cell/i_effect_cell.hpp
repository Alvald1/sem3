#ifndef I_EFFECT_CELL_HPP
#define I_EFFECT_CELL_HPP

#include <cstddef>

/**
 * @brief Interface for effect cells
 * 
 * This interface defines the contract for all effect cells in the game.
 */
class IEffectCell {
  public:
    /**
     * @brief Virtual destructor
     */
    virtual ~IEffectCell() = default;

    /**
     * @brief Apply the effect and return its value
     * @return int The effect value
     */
    virtual int give_effect() = 0;

    /**
     * @brief Set the effect parameters
     * @param amount The effect amount/value
     * @param time Duration of the effect
     */
    virtual void set_effect(int amount, size_t time) = 0;
};

#endif // I_EFFECT_CELL_HPP
