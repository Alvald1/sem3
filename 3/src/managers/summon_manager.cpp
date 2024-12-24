#include "summon_manager.hpp"

#include "map_manager.hpp"
#include "queue/entity/builder/entity_director.hpp"
#include "queue/entity/builder/moral_troop_builder.hpp"
#include "utilities/type_system.hpp"

SummonManager* SummonManager::instance_ = nullptr;

void
SummonManager::summon(Summoner& summoner, const Ability& ability, const Position& position) {
    auto type = TypeSystem::getTroopType(ability.get_creature().get_type());
    switch (type) {
        case TroopType::MORAL: create_moral(summoner, ability, position); break;
        case TroopType::AMORAL: create_amoral(summoner, ability, position); break;
        default: break;
    }
}

void
SummonManager::create_moral(Summoner& summoner, const Ability& ability, const Position& position) {
    auto summoner_pos = MapManager::getInstance().get_entity_position(summoner.get_id());
    summoner.spend_energy(ability.get_energy());
    auto troop = EntityDirector::createMoralTroop(ability, 0);
    MapManager::getInstance().add_entity(troop.get_id(), position + summoner_pos.value());
    EntityManager::getInstance().add_entity(std::make_unique<MoralTroop>(troop));
}

void
SummonManager::create_amoral(Summoner& summoner, const Ability& ability, const Position& position) {
    auto summoner_pos = MapManager::getInstance().get_entity_position(summoner.get_id());
    summoner.spend_energy(ability.get_energy());
    auto troop = EntityDirector::createAmoralTroop(ability);
    MapManager::getInstance().add_entity(troop.get_id(), position + summoner_pos.value());
    EntityManager::getInstance().add_entity(std::make_unique<AmoralTroop>(troop));
}
