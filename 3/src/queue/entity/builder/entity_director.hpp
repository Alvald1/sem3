#ifndef ENTITY_DIRECTOR_HPP
#define ENTITY_DIRECTOR_HPP

#include "amoral_troop_builder.hpp"
#include "moral_troop_builder.hpp"
#include "summoner_builder.hpp"

/**
 * @brief Director class that coordinates the construction of different entities
 * 
 * This class provides static methods to create different types of entities
 * using their respective builders.
 */
class EntityDirector {
  public:
    /**
     * @brief Creates a MoralTroop with specified parameters
     * @param ability The ability for the troop
     * @param moral_value The moral value of the troop
     * @param id_summoner The ID of the summoner
     * @return Constructed MoralTroop object
     */
    static MoralTroop
    createMoralTroop(Ability ability, int moral_value, size_t id_summoner) {
        return MoralTroopBuilder(ability).moral_value(moral_value).id_summoner(id_summoner).build();
    }

    /**
     * @brief Creates an AmoralTroop with specified parameters
     * @param ability The ability for the troop
     * @param id_summoner The ID of the summoner
     * @return Constructed AmoralTroop object
     */
    static AmoralTroop
    createAmoralTroop(Ability ability, size_t id_summoner) {
        return AmoralTroopBuilder(ability).id_summoner(id_summoner).build();
    }

    /**
     * @brief Creates a Summoner with specified parameters
     * @param ability The ability for the summoner
     * @param max_energy The maximum energy capacity
     * @param accum_index The accumulation index
     * @return Constructed Summoner object
     */
    static Summoner
    createSummoner(Ability ability, size_t max_energy, size_t accum_index) {
        return SummonerBuilder(ability).max_energy(max_energy).accum_index(accum_index).build();
    }
};

#endif // ENTITY_DIRECTOR_HPP
