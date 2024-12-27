#ifndef AMORAL_TROOP_HPP
#define AMORAL_TROOP_HPP

#include "base_troop.hpp"

/**
 * @brief A troop class without moral characteristics
 * 
 * AmoralTroop represents a basic troop without moral behavior,
 * inheriting only from BaseTroop without additional functionality.
 */
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
    /**
     * @brief Private constructor used by AmoralTroopBuilder
     * @param ability The ability configuration for the troop
     */
    explicit AmoralTroop(const Ability& ability) : BaseTroop(ability) {}
};

#endif // AMORAL_TROOP_HPP
