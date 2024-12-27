#ifndef SUMMON_MANAGER_HPP
#define SUMMON_MANAGER_HPP

#include "queue/entity/entity.hpp"
#include "queue/entity/summoner.hpp"
#include "schools/school/ability/ability.hpp"
#include "schools/school/school.hpp"
#include "utilities/position.hpp"

/**
 * @brief Manager class for handling summoning of troops
 * 
 * Singleton class responsible for creating and managing the summoning of troops
 * by summoner entities.
 */
class SummonManager {
  private:
    static SummonManager* instance_;
    SummonManager() = default;

    /**
     * @brief Creates a moral troop
     * @param summoner The summoner entity creating the troop
     * @param ability The ability used to create the troop
     * @param position The position where the troop should be summoned
     * @throws InvalidPositionException if position is invalid
     */
    void create_moral(Summoner& summoner, const Ability& ability, const Position& position);

    /**
     * @brief Creates an amoral troop
     * @param summoner The summoner entity creating the troop
     * @param ability The ability used to create the troop
     * @param position The position where the troop should be summoned
     * @throws InvalidPositionException if position is invalid
     */
    void create_amoral(Summoner& summoner, const Ability& ability, const Position& position);

  public:
    /**
     * @brief Gets the singleton instance of SummonManager
     * @return Reference to the SummonManager instance
     */
    static SummonManager&
    getInstance() { // убедитесь, что возвращается ссылка
        if (instance_ == nullptr) {
            instance_ = new SummonManager();
        }
        return *instance_;
    }

    /**
     * @brief Destroys the singleton instance
     */
    static void
    destroyInstance() {
        delete instance_;
        instance_ = nullptr;
    }

    SummonManager(const SummonManager&) = delete;
    SummonManager& operator=(const SummonManager&) = delete;

    /**
     * @brief Summons a new troop
     * @param summoner The summoner entity creating the troop
     * @param ability The ability used to create the troop
     * @param position The position where the troop should be summoned
     * @throws InvalidTroopTypeException if troop type is invalid
     * @throws InvalidPositionException if position is invalid
     */
    void summon(Summoner& summoner, const Ability& ability, const Position& position);
};

#endif // SUMMON_MANAGER_HPP
