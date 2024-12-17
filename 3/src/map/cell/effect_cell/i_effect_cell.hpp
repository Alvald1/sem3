#ifndef I_EFFECT_CELL_HPP
#define I_EFFECT_CELL_HPP

#include <cstddef>

class IEffectCell {
  public:
    virtual ~IEffectCell() = default;
    virtual int give_effect() = 0;
    virtual void set_effect(int amount, size_t time) = 0;
};

#endif // I_EFFECT_CELL_HPP
