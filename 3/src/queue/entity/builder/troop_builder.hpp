#ifndef TROOP_BUILDER_HPP
#define TROOP_BUILDER_HPP

#include "../troop/amoral_troop.hpp"
#include "../troop/moral_troop.hpp"
#include "entity_builder.hpp"

class TroopBuilder : public EntityBuilder {
  private:
    bool is_moral;
    int moral_value;

  public:
    explicit TroopBuilder(const Ability& ability) : EntityBuilder(ability), is_moral(false), moral_value(0) {}

    TroopBuilder&
    setMoral(bool moral) {
        is_moral = moral;
        return *this;
    }

    TroopBuilder&
    setMoralValue(int value) {
        moral_value = value;
        return *this;
    }

    [[nodiscard]] Entity*
    build() override {
        if (is_moral) {
            return new MoralTroop(ability, moral_value);
        }
        return new AmoralTroop(ability);
    }
};

#endif // TROOP_BUILDER_HPP
