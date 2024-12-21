#ifndef SUMMON_MANAGER_HPP
#define SUMMON_MANAGER_HPP

#include "../queue/entity/entity.hpp"
#include "../queue/entity/summoner.hpp"
#include "../schools/school/ability/ability.hpp"
#include "../schools/school/school.hpp"

class SummonManager {
private:
    static SummonManager* instance_;
    SummonManager() = default;

public:
    static SummonManager& getInstance() {
        if (instance_ == nullptr) {
            instance_ = new SummonManager();
        }
        return *instance_;
    }

    SummonManager(const SummonManager&) = delete;
    SummonManager& operator=(const SummonManager&) = delete;

    void upgrade(Summoner& summoner, School& school);
    Entity make_entity(const Ability& ability);
};

#endif // SUMMON_MANAGER_HPP
