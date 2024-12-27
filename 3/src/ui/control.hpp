#ifndef CONTROL_HPP
#define CONTROL_HPP

#include <functional>
#include <optional>
#include <utility>
#include <vector>

#include "schools/school/ability/ability.hpp"
#include "utilities/position.hpp"

/**
 * @brief Control class for handling user input and game control
 * 
 * The Control class implements a singleton pattern and manages all user input
 * and control flow in the game.
 */
class Control {
  public:
    /**
     * @brief Enumeration for possible summoner actions
     */
    enum class SummonerAction {
        SUMMON_TROOP,      /**< Summon a new troop */
        ACCUMULATE_ENERGY, /**< Accumulate energy */
        UPGRADE_SCHOOL,    /**< Upgrade the school */
        SKIP_TURN          /**< Skip the current turn */
    };

    /**
     * @brief Enumeration for possible troop actions
     */
    enum class TroopAction {
        MOVE,     /**< Move the troop */
        EFFECT,   /**< Apply an effect */
        ATTACK,   /**< Attack another entity */
        SKIP_TURN /**< Skip the current turn */
    };

  private:
    static Control* instance;
    Control() = default;
    size_t current_ability_selection{0};

  public:
    /**
     * @brief Get singleton instance of Control
     * @return Reference to Control instance
     */
    static Control& getInstance();

    // Delete copy constructor and assignment operator
    Control(const Control&) = delete;
    Control& operator=(const Control&) = delete;

    // Add control methods here
    void handleInput();
    void update();

    /**
     * @brief Get action choice for summoner
     * @return Selected SummonerAction
     */
    [[nodiscard]] SummonerAction get_summoner_action() const;

    /**
     * @brief Get ability choice from available abilities
     * @param abilities Vector of available abilities
     * @param current_energy Current energy available
     * @param current_experience Current experience available
     * @return Selected ability ID or SIZE_MAX if cancelled
     */
    [[nodiscard]] size_t get_ability_choice(const std::vector<std::reference_wrapper<const Ability>>& abilities,
                                            size_t current_energy, size_t current_experience);

    [[nodiscard]] Position get_position_choice(Position current_pos) const;

    /**
     * @brief Get action choice for troop
     * @return Selected TroopAction
     */
    [[nodiscard]] TroopAction get_troop_action() const;

    /**
     * @brief Get map size from user input
     * @return Pair of integers representing width and height
     */
    std::pair<int, int> get_map_size() const;

    /**
     * @brief Handle basic input
     * @return true if should continue, false if should exit
     */
    bool handle_input();

    std::optional<size_t> select_summoner(const std::vector<std::reference_wrapper<const Ability>>& summoners,
                                          const std::vector<bool>& selected, int current_player) const;

    ~Control() = default;
};

#endif // CONTROL_HPP
