#ifndef AMORAL_TROOP_HPP
#define AMORAL_TROOP_HPP

#include "base_troop.hpp"

class AmoralTroop : public BaseTroop {
    friend class AmoralTroopBuilder;

  public:
    // Rule of five
    AmoralTroop(const AmoralTroop&) = default;
    AmoralTroop& operator=(const AmoralTroop&) = default;
    AmoralTroop(AmoralTroop&&) noexcept = default;
    AmoralTroop& operator=(AmoralTroop&&) noexcept = default;
    ~AmoralTroop() override = default;

  private:
    explicit AmoralTroop(const Ability& ability) : BaseTroop(ability) {}
};

#endif // AMORAL_TROOP_HPP
