#ifndef MORAL_TROOP_HPP
#define MORAL_TROOP_HPP

#include "base_troop.hpp"
#include "i_moral.hpp"

/**
 * @brief A troop class that implements moral behavior
 * 
 * MoralTroop represents a troop with moral characteristics,
 * implementing the IMoral interface for morale manipulation.
 */
class MoralTroop : public BaseTroop, public IMoral {
    friend class MoralTroopBuilder;

  public:
    // Rule of five
    MoralTroop(const MoralTroop&) = default;
    MoralTroop& operator=(const MoralTroop&) = default;
    MoralTroop(MoralTroop&&) noexcept = default;
    MoralTroop& operator=(MoralTroop&&) noexcept = default;
    ~MoralTroop() override = default;

    // IMoral interface implementation
    /**
     * @brief Increases the morale of the troop
     * @param amount The amount by which to increase morale
     */
    inline void
    increase_morale(std::size_t amount) override {
        moral += amount;
    }

    /**
     * @brief Decreases the morale of the troop
     * @param amount The amount by which to decrease morale
     */
    inline void
    decrease_morale(std::size_t amount) override {
        moral -= amount;
    }

    /**
     * @brief Balances the morale towards zero
     * @param amount The amount by which to adjust morale
     * 
     * If morale is positive, decreases it; if negative, increases it.
     */
    void
    balance_morale(std::size_t amount) override {
        if (moral > 0) {
            decrease_morale(amount);
        } else if (moral < 0) {
            increase_morale(amount);
        }
    }

    // Getter and setter for moral
    /**
     * @brief Gets the current moral value
     * @return Current moral value
     */
    [[nodiscard]] inline int
    get_moral() const noexcept {
        return moral;
    }

    /**
     * @brief Sets a new moral value
     * @param new_moral The new moral value to set
     */
    inline void
    set_moral(int new_moral) noexcept {
        moral = new_moral;
    }

  private:
    /** @brief Current moral value of the troop */
    int moral;

    /**
     * @brief Private constructor used by MoralTroopBuilder
     * @param ability The ability configuration for the troop
     */
    explicit MoralTroop(const Ability& ability) : BaseTroop(ability) {}
};

#endif // MORAL_TROOP_HPP
