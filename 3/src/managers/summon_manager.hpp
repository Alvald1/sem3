#ifndef SUMMON_MANAGER_HPP
#define SUMMON_MANAGER_HPP

#include "queue/entity/entity.hpp"
#include "queue/entity/summoner.hpp"
#include "schools/school/ability/ability.hpp"
#include "schools/school/school.hpp"
#include "utilities/position.hpp"

class SummonManager {
  private:
    static SummonManager* instance_;
    SummonManager() = default;

    void create_moral(Summoner& summoner, const Ability& ability, const Position& position);
    void create_amoral(Summoner& summoner, const Ability& ability, const Position& position);

  public:
    static SummonManager&
    getInstance() { // убедитесь, что возвращается ссылка
        if (instance_ == nullptr) {
            instance_ = new SummonManager();
        }
        return *instance_;
    }

    static void
    destroyInstance() {
        delete instance_;
        instance_ = nullptr;
    }

    SummonManager(const SummonManager&) = delete;
    SummonManager& operator=(const SummonManager&) = delete;

    void summon(Summoner& summoner, const Ability& ability, const Position& position);
};

#endif // SUMMON_MANAGER_HPP
