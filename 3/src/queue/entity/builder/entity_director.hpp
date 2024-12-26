#ifndef ENTITY_DIRECTOR_HPP
#define ENTITY_DIRECTOR_HPP

#include "amoral_troop_builder.hpp"
#include "moral_troop_builder.hpp"
#include "summoner_builder.hpp"

class EntityDirector {
  public:
    static MoralTroop
    createMoralTroop(Ability ability, int moral_value, size_t id_summoner) {
        return MoralTroopBuilder(ability).moral_value(moral_value).id_summoner(id_summoner).build();
    }

    static AmoralTroop
    createAmoralTroop(Ability ability, size_t id_summoner) {
        return AmoralTroopBuilder(ability).id_summoner(id_summoner).build();
    }

    static Summoner
    createSummoner(Ability ability, size_t max_energy, size_t accum_index) {
        return SummonerBuilder(ability).max_energy(max_energy).accum_index(accum_index).build();
    }
};

#endif // ENTITY_DIRECTOR_HPP
