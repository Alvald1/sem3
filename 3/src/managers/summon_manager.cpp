#include "summon_manager.hpp"
#include "utilities/exceptions.hpp"

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
        default: throw InvalidTroopTypeException();
    }
}

void
SummonManager::create_moral(Summoner& summoner, const Ability& ability, const Position& position) {
    auto summoner_pos = MapManager::getInstance().get_entity_position(summoner.get_id());
    if (!summoner_pos.has_value() || position.manhattan_distance(summoner_pos.value()) > 2) {
        throw InvalidPositionException();
    }
    if (!MapManager::getInstance().is_cell_passable(position) || MapManager::getInstance().is_cell_occupied(position)) {
        throw InvalidPositionException();
    }
    auto troop = EntityDirector::createMoralTroop(ability, 0, summoner.get_id());
    summoner.add_ownership(troop.get_id());
    MapManager::getInstance().add_entity(troop.get_id(), position);
    EntityManager::getInstance().add_entity(std::make_unique<MoralTroop>(troop));
}

void
SummonManager::create_amoral(Summoner& summoner, const Ability& ability, const Position& position) {
    auto summoner_pos = MapManager::getInstance().get_entity_position(summoner.get_id());
    if (!summoner_pos.has_value() || position.manhattan_distance(summoner_pos.value()) > 2) {
        throw InvalidPositionException();
    }
    if (!MapManager::getInstance().is_cell_passable(position) || MapManager::getInstance().is_cell_occupied(position)) {
        throw InvalidPositionException();
    }
    auto troop = EntityDirector::createAmoralTroop(ability, summoner.get_id());
    summoner.add_ownership(troop.get_id());
    MapManager::getInstance().add_entity(troop.get_id(), position);
    EntityManager::getInstance().add_entity(std::make_unique<AmoralTroop>(troop));
}
