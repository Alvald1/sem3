#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include "../game/game.hpp"
#include "../queue/queue.hpp"
#include "../schools/schools.hpp"
#include "action_manager.hpp"
#include "damage_manager.hpp"
#include "map_manager.hpp"
#include "summon_manager.hpp"

class GameManager : public Game {
  public:
    GameManager();
    ~GameManager();
    void do_step();

  private:
    MapManager map_manager_;
    SortQueue queue_;
    Schools schools_;
    DamageManager damage_manager_;
    ActionManager action_manager_;
    SummonManager summon_manager_;
};

#endif // GAME_MANAGER_HPP
