#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include "action_manager.hpp"
#include "damage_manager.hpp"
#include "entity_manager.hpp"
#include "map_manager.hpp"
#include "queue/queue.hpp"
#include "schools/schools.hpp"
#include "summon_manager.hpp"

class GameManager {
  private:
    static GameManager* instance_;

    // Приватный конструктор с инициализацией членов
    GameManager() = default;

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
