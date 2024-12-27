#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include "action_manager.hpp"
#include "damage_manager.hpp"
#include "entity_manager.hpp"
#include "map_manager.hpp"
#include "queue/queue.hpp"
#include "schools/schools.hpp"
#include "summon_manager.hpp"

/**
 * @brief Main game controller that manages the game loop and turn sequence
 *
 * This singleton class coordinates all other managers and handles the main game logic flow.
 */
class GameManager {
  private:
    static GameManager* instance_;

    // Приватный конструктор с инициализацией членов
    GameManager() = default;

  public:
    /**
     * @brief Get the singleton instance of GameManager
     * @return Reference to the GameManager instance
     */
    static GameManager&
    getInstance() {
        if (instance_ == nullptr) {
            instance_ = new GameManager();
        }
        return *instance_;
    }

    /**
     * @brief Destroy the singleton instance
     */
    static void
    destroyInstance() {
        delete instance_;
        instance_ = nullptr;
    }

    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;

    ~GameManager() = default;

    /**
     * @brief Execute a single game step
     *
     * Processes cell effects, handles current entity's action, and advances to next turn
     */
    void do_step();
};

#endif // GAME_MANAGER_HPP
