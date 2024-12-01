#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include "../core/game.hpp"
#include "map_manager.hpp"
#include "damage_manager.hpp"
#include "action_manager.hpp"
#include "summon_manager.hpp"
#include "../core/queue.hpp"
#include "../schools/schools.hpp"

class game_manager : public game {
public:
    game_manager();
    ~game_manager();
    void do_step();

private:
    map_manager map_manager_;
    queue queue_;
    schools schools_;
    damage_manager damage_manager_;
    action_manager action_manager_;
    summon_manager summon_manager_;
};

#endif // GAME_MANAGER_HPP
