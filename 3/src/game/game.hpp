#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include "json_parser.hpp"
#include "managers/action_manager.hpp"
#include "managers/game_manager.hpp"
#include "map/map.hpp"
#include "queue/entity/summoner.hpp"
#include "queue/entity/troop/base_troop.hpp"
#include "ui/board.hpp"
#include "ui/control.hpp"
#include "ui/view.hpp"

/**
 * @class Game
 * @brief Main game class that controls the game flow and initialization.
 * 
 * This class is responsible for initializing the game state, loading configurations,
 * managing the game loop, and handling user input.
 */
class Game {
  private:
    JsonParser parser_;             ///< Parser for game configurations
    std::unique_ptr<Map> game_map_; ///< Game map instance

  public:
    /**
     * @brief Default constructor
     */
    Game();

    /**
     * @brief Destructor
     * Handles cleanup of game resources
     */
    ~Game();

    /**
     * @brief Starts the game
     * Initializes game components and runs the main game loop
     */
    void start();

    /**
     * @brief Loads game configurations
     * @throws std::runtime_error If loading configurations fails
     */
    void load();
};

#endif // GAME_HPP
