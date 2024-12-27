#ifndef SUMMONER_BUILDER_HPP
#define SUMMONER_BUILDER_HPP

#include "queue/entity/summoner.hpp"

/**
 * @brief Builder class for creating Summoner objects
 * 
 * This class implements the Builder pattern to construct Summoner objects
 * with various parameters in a step-by-step manner.
 */
class SummonerBuilder {
  private:
    Summoner summoner_;

  public:
    /**
     * @brief Constructs a new Summoner Builder object
     * @param ability The ability that the summoner will possess
     */
    explicit SummonerBuilder(Ability ability) : summoner_(ability) {}

    /**
     * @brief Sets the maximum energy for the summoner
     * @param energy The energy value to set
     * @return Reference to the builder for method chaining
     */
    SummonerBuilder&
    max_energy(size_t energy) {
        summoner_.energy = energy;
        summoner_.max_energy = energy;
        return *this;
    }

    /**
     * @brief Sets the accumulation index for the summoner
     * @param index The index value to set
     * @return Reference to the builder for method chaining
     */
    SummonerBuilder&
    accum_index(size_t index) {
        summoner_.accum_index = index;
        return *this;
    }

    /**
     * @brief Builds and returns the final Summoner object
     * @return Constructed Summoner object
     */
    Summoner
    build() {
        return std::move(summoner_);
    }
};

#endif // SUMMONER_BUILDER_HPP
