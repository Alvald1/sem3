#ifndef AMORAL_TROOP_BUILDER_HPP
#define AMORAL_TROOP_BUILDER_HPP

#include "queue/entity/troop/amoral_troop.hpp"

class AmoralTroopBuilder {
  public:
    explicit AmoralTroopBuilder(Ability ability) : amoral_troop_(ability) {}

    AmoralTroopBuilder&
    id_summoner(int value) {
        amoral_troop_.id_summoner_ = value;
        return *this;
    }

    AmoralTroop
    build() {
        return std::move(amoral_troop_);
    }

  private:
    AmoralTroop amoral_troop_;
};

#endif // AMORAL_TROOP_BUILDER_HPP
