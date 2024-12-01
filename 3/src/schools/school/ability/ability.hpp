#ifndef ABILITY_HPP
#define ABILITY_HPP

#include "utilities/name_id.hpp"
#include "creature/creature.hpp"

class Ability : public NameID {
private:
    Creature* creature;
    size_t level;
    size_t energy;
    size_t upgrade_index;
    size_t experience;

public:
    Ability(size_t id, const std::string& name, size_t level = 0, size_t energy = 0, 
           size_t upgrade_index = 0, size_t experience = 0, Creature* creature = nullptr)
        : NameID(id, name), level(level), energy(energy), 
          upgrade_index(upgrade_index), experience(experience), creature(creature) {}

    // Getters
    Creature* getCreature() const { return creature; }
    size_t getLevel() const { return level; }
    size_t getEnergy() const { return energy; }
    size_t getUpgradeIndex() const { return upgrade_index; }
    size_t getExperience() const { return experience; }

    // Setters
    void setCreature(Creature* newCreature) { creature = newCreature; }
    void setLevel(size_t newLevel) { level = newLevel; }
    void setEnergy(size_t newEnergy) { energy = newEnergy; }
    void setUpgradeIndex(size_t newUpgradeIndex) { upgrade_index = newUpgradeIndex; }
    void setExperience(size_t newExperience) { experience = newExperience; }
};

#endif // ABILITY_HPP
