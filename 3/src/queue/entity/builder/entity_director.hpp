#ifndef ENTITY_DIRECTOR_HPP
#define ENTITY_DIRECTOR_HPP

#include "summoner_builder.hpp"
#include "troop_builder.hpp"

class EntityDirector {
  public:
    static Entity
    createMoralTroop(Ability ability, int moral_value) {
        return TroopBuilder(ability).moral(true).moral_value(moral_value).build();
    }

    static Entity
    createAmoralTroop(Ability ability) {
        return TroopBuilder(ability).moral(false).build();
    }

    static Summoner
    createSummoner(Ability ability, size_t max_energy, size_t accum_index) {
        return SummonerBuilder(ability).max_energy(max_energy).accum_index(accum_index).build();
    }
};

#endif // ENTITY_DIRECTOR_HPP
