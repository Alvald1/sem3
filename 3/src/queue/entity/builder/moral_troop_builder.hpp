#ifndef MORAL_TROOP_BUILDER_HPP
#define MORAL_TROOP_BUILDER_HPP

#include "queue/entity/troop/moral_troop.hpp"

/**
 * @brief Builder class for creating MoralTroop objects
 * 
 * This class implements the Builder pattern to construct MoralTroop objects
 * with various parameters in a step-by-step manner.
 */
class MoralTroopBuilder {
  public:
    /**
     * @brief Constructs a new Moral Troop Builder object
     * @param ability The ability that the moral troop will possess
     */
    explicit MoralTroopBuilder(Ability ability) : moral_troop_(ability) {}

    /**
     * @brief Sets the moral value for the troop
     * @param value The moral value to set
     * @return Reference to the builder for method chaining
     */
    MoralTroopBuilder&
    moral_value(int value) {
        moral_troop_.moral = value;
        return *this;
    }

    /**
     * @brief Sets the summoner ID for the troop
     * @param value The summoner ID to set
     * @return Reference to the builder for method chaining
     */
    MoralTroopBuilder&
    id_summoner(int value) {
        moral_troop_.id_summoner_ = value;
        return *this;
    }

    /**
     * @brief Builds and returns the final MoralTroop object
     * @return Constructed MoralTroop object
     */
    MoralTroop
    build() {
        return std::move(moral_troop_);
    }

  private:
    MoralTroop moral_troop_;
};

#endif // MORAL_TROOP_BUILDER_HPP
