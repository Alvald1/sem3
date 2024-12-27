#include "singleton_manager.hpp"
#include "action_manager.hpp"
#include "damage_manager.hpp"
#include "entity_manager.hpp"
#include "game_manager.hpp"
#include "map_manager.hpp"
#include "schools/schools.hpp"
#include "summon_manager.hpp"

void
SingletonManager::initializeAll() { // Добавляем определение
    Schools::getInstance();
    MapManager::getInstance();
    EntityManager::getInstance();
    DamageManager::getInstance();
    SummonManager::getInstance();
    ActionManager::getInstance();
    GameManager::getInstance();
}

void
SingletonManager::destroyAll() { // Добавляем определение
    GameManager::destroyInstance();
    ActionManager::destroyInstance();
    SummonManager::destroyInstance();
    DamageManager::destroyInstance();
    EntityManager::destroyInstance();
    MapManager::destroyInstance();
    Schools::destroyInstance();
}
