#ifndef AMORAL_TROOP_BUILDER_HPP
#define AMORAL_TROOP_BUILDER_HPP

#include "queue/entity/troop/amoral_troop.hpp"

/**
 * @brief Builder class for creating AmoralTroop objects
 * 
 * This class implements the Builder pattern to construct AmoralTroop objects
 * with various parameters in a step-by-step manner.
 */
class AmoralTroopBuilder {
  public:
    /**
     * @brief Constructs a new Amoral Troop Builder object
     * @param ability The ability that the amoral troop will possess
     */
    explicit AmoralTroopBuilder(Ability ability) : amoral_troop_(ability) {}

    /**
     * @brief Sets the summoner ID for the troop
     * @param value The summoner ID to set
     * @return Reference to the builder for method chaining
     */
    AmoralTroopBuilder&
    id_summoner(int value) {
        amoral_troop_.id_summoner_ = value;
        return *this;
    }

    /**
     * @brief Builds and returns the final AmoralTroop object
     * @return Constructed AmoralTroop object
     */
    AmoralTroop
    build() {
        return std::move(amoral_troop_);
    }

  private:
    AmoralTroop amoral_troop_;
};

#endif // AMORAL_TROOP_BUILDER_HPP
