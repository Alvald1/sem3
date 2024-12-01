#ifndef MORAL_TROOP_HPP
#define MORAL_TROOP_HPP

#include "base_troop.hpp"
#include "i_moral.hpp"

class MoralTroop : public BaseTroop, public IMoral {
private:
    int moral;

public:
    MoralTroop(size_t id, const std::string& name, size_t initiative, size_t max_hp,
               size_t speed, size_t damage, size_t range, size_t type, int moral = 0)
        : BaseTroop(id, name, initiative, max_hp, speed, damage, range, type),
          moral(moral) {}

    // IMoral interface implementation
    void increase_morale(size_t amount) override { moral += amount; }
    void decrease_morale(size_t amount) override { moral -= amount; }
    void balance_morale() override { moral = 0; }

    // Getter and setter for moral
    int getMoral() const { return moral; }
    void setMoral(int newMoral) { moral = newMoral; }
};

#endif // MORAL_TROOP_HPP
