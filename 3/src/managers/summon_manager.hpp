#ifndef SUMMON_MANAGER_HPP
#define SUMMON_MANAGER_HPP

#include "../ability/ability.hpp"
#include "../queue/entity/entity.hpp"
#include "../queue/entity/summoner.hpp"
#include "../schools/school/school.hpp"

class summon_manager {
public:
    void upgrade(summoner& summoner, school& school);
    entity make_entity(const ability& ability);
};

#endif // SUMMON_MANAGER_HPP
