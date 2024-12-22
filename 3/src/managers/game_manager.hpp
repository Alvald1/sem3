#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include "../game/game.hpp"
#include "../queue/queue.hpp"
#include "../schools/schools.hpp"
#include "action_manager.hpp"
#include "damage_manager.hpp"
#include "entity_manager.hpp"
#include "map_manager.hpp"
#include "summon_manager.hpp"

class GameManager : public Game {
  private:
    static GameManager* instance_;

    // Приватный конструктор с инициализацией членов
    GameManager()
        : entity_manager_(EntityManager::getInstance()), map_manager_(MapManager::getInstance()),
          damage_manager_(DamageManager::getInstance()), action_manager_(ActionManager::getInstance()),
          summon_manager_(SummonManager::getInstance()) {}

    // Члены класса
    EntityManager& entity_manager_;
    MapManager& map_manager_;
    DamageManager& damage_manager_;
    ActionManager& action_manager_;
    SummonManager& summon_manager_;

  public:
    static GameManager&
    getInstance() {
        if (instance_ == nullptr) {
            instance_ = new GameManager();
        }
        return *instance_;
    }

    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;

    ~GameManager();
    void do_step();
};

#endif // GAME_MANAGER_HPP
