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

class Game {
  private:
    JsonParser parser_;
    std::unique_ptr<Map> game_map_;

  public:
    Game();
    ~Game();
    void start();
    void load();
};

#endif // GAME_HPP
