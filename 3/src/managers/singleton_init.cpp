#include "action_manager.hpp"
#include "damage_manager.hpp"
#include "entity_manager.hpp"
#include "game_manager.hpp"
#include "map_manager.hpp"
#include "summon_manager.hpp"

// Initialize static members
Schools* Schools::instance_ = nullptr;
ActionManager* ActionManager::instance_ = nullptr;
DamageManager* DamageManager::instance_ = nullptr;
EntityManager* EntityManager::instance_ = nullptr;
GameManager* GameManager::instance_ = nullptr;
MapManager* MapManager::instance_ = nullptr;
SummonManager* SummonManager::instance_ = nullptr;
