#ifndef TROOP_BUILDER_HPP
#define TROOP_BUILDER_HPP

#include <memory>
#include "queue/entity/troop/amoral_troop.hpp"
#include "queue/entity/troop/moral_troop.hpp"

class TroopBuilder {

  public:
    explicit TroopBuilder(Ability ability) : ability(ability) {}

    TroopBuilder&
    moral(bool moral) noexcept {
        is_moral = moral;
        return *this;
    }

    TroopBuilder&
    moral_value(int value) noexcept {
        moral_value_ = value;
        return *this;
    }

    Entity
    build() {
        if (is_moral) {
            return MoralTroop(ability, moral_value_);
        }
        return AmoralTroop(ability);
    }

  private:
    Ability ability;
    bool is_moral;
    int moral_value_;
};

#endif // TROOP_BUILDER_HPP
