#ifndef SUMMON_MANAGER_HPP
#define SUMMON_MANAGER_HPP

#include "../queue/entity/entity.hpp"
#include "../queue/entity/summoner.hpp"
#include "../schools/school/ability/ability.hpp"
#include "../schools/school/school.hpp"

class SummonManager {
  public:
    void upgrade(Summoner& summoner, School& school);
    Entity make_entity(const Ability& ability);
};

#endif // SUMMON_MANAGER_HPP
