#ifndef I_EFFECT_CELL_HPP
#define I_EFFECT_CELL_HPP

#include "../../../entity/entity_id.hpp"

class IEffectCell {
public:
    virtual ~IEffectCell() = default;
    virtual void give_effect(EntityID entity_id) = 0;
};

#endif // I_EFFECT_CELL_HPP
