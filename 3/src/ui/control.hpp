#ifndef CONTROL_HPP
#define CONTROL_HPP

#include <functional>
#include <vector>

#include "schools/school/ability/ability.hpp"
#include "utilities/position.hpp"

class Control {
  public:
    enum class SummonerAction { SUMMON_TROOP, ACCUMULATE_ENERGY, UPGRADE_SCHOOL, SKIP_TURN };
    enum class TroopAction { MOVE, EFFECT, ATTACK, SKIP_TURN };

  private:
    static Control* instance;
    Control() = default;

  public:
    static Control* getInstance();

    // Delete copy constructor and assignment operator
    Control(const Control&) = delete;
    Control& operator=(const Control&) = delete;

    // Add control methods here
    void handleInput();
    void update();
    [[nodiscard]] SummonerAction get_summoner_action() const;
    [[nodiscard]] size_t get_ability_choice() const;
    [[nodiscard]] Position get_position_choice() const;
    [[nodiscard]] TroopAction get_troop_action() const;

    ~Control() = default;
};

#endif // CONTROL_HPP
