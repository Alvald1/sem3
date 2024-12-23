#ifndef SUMMONER_BUILDER_HPP
#define SUMMONER_BUILDER_HPP

#include "../summoner.hpp"
#include "entity_builder.hpp"

class SummonerBuilder : public EntityBuilder {
  private:
    size_t max_energy;
    size_t accum_index;

  public:
    explicit SummonerBuilder(const Ability& ability) : EntityBuilder(ability), max_energy(100), accum_index(1) {}

    SummonerBuilder&
    setMaxEnergy(size_t energy) {
        max_energy = energy;
        return *this;
    }

    SummonerBuilder&
    setAccumIndex(size_t index) {
        accum_index = index;
        return *this;
    }

    [[nodiscard]] Entity*
    build() override {
        return new Summoner(ability, max_energy, accum_index);
    }
};

#endif // SUMMONER_BUILDER_HPP
