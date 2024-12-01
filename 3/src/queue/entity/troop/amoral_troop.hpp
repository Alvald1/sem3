#ifndef AMORAL_TROOP_HPP
#define AMORAL_TROOP_HPP

#include "base_troop.hpp"

class AmoralTroop : public BaseTroop {
public:
    AmoralTroop(size_t id, const std::string& name, size_t initiative, size_t max_hp,
                size_t speed, size_t damage, size_t range, size_t type)
        : BaseTroop(id, name, initiative, max_hp, speed, damage, range, type) {}
};

#endif // AMORAL_TROOP_HPP
