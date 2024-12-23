#ifndef ENTITY_DIRECTOR_HPP
#define ENTITY_DIRECTOR_HPP

#include "entity_builder.hpp"
#include "summoner_builder.hpp"
#include "troop_builder.hpp"

class EntityDirector {
  public:
    static Entity*
    createMoralTroop(const Ability& ability, int moral_value) {
        return TroopBuilder(ability).setMoral(true).setMoralValue(moral_value).build();
    }

    static Entity*
    createAmoralTroop(const Ability& ability) {
        return TroopBuilder(ability).setMoral(false).build();
    }

    static Entity*
    createStandardSummoner(const Ability& ability) {
        return SummonerBuilder(ability).build();
    }

    static Entity*
    createCustomSummoner(const Ability& ability, size_t max_energy, size_t accum_index) {
        return SummonerBuilder(ability).setMaxEnergy(max_energy).setAccumIndex(accum_index).build();
    }
};

#endif // ENTITY_DIRECTOR_HPP
