#ifndef MORAL_TROOP_BUILDER_HPP
#define MORAL_TROOP_BUILDER_HPP

#include "queue/entity/troop/moral_troop.hpp"

class MoralTroopBuilder {
  public:
    explicit MoralTroopBuilder(Ability ability) : moral_troop_(ability) {}

    MoralTroopBuilder&
    moral_value(int value) {
        moral_troop_.moral = value;
        return *this;
    }

    MoralTroopBuilder&
    id_summoner(int value) {
        moral_troop_.id_summoner_ = value;
        return *this;
    }

    MoralTroop
    build() {
        return std::move(moral_troop_);
    }

  private:
    MoralTroop moral_troop_;
};

#endif // MORAL_TROOP_BUILDER_HPP
