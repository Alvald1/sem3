#include "schools_director.hpp"

Creature
SchoolsDirector::createCreature(const std::string& name, size_t speed, size_t damage, size_t range, size_t type,
                                size_t initiative) {
    return Creature::create(name).speed(speed).damage(damage).range(range).type(type).initiative(initiative).build();
}

Ability
SchoolsDirector::createAbility(const std::string& name, Creature creature, size_t level, size_t energy,
                               size_t experience, size_t count) {
    return Ability::create(name, std::move(creature))
        .level(level)
        .energy(energy)
        .experience(experience)
        .count(count)
        .build();
}

School
SchoolsDirector::createSchool(const std::string& name, const std::vector<Ability>& abilities) {
    auto builder = School::create(name);
    for (const auto& ability : abilities) {
        builder.addAbility(ability);
    }
    return builder.build();
}
