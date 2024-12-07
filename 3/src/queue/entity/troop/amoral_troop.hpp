#ifndef AMORAL_TROOP_HPP
#define AMORAL_TROOP_HPP

#include "base_troop.hpp"

class AmoralTroop : public BaseTroop {
  public:
    explicit AmoralTroop(const Ability& ability) : BaseTroop(ability) {}
};

#endif // AMORAL_TROOP_HPP
