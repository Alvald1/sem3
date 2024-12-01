#ifndef SUMMONER_HPP
#define SUMMONER_HPP

#include <unordered_map>
#include "entity.hpp"
#include "../../schools/school/school.hpp"
#include "../../level/level.hpp"

class Summoner : public Entity {
private:
    size_t energy;
    const size_t max_energy;
    size_t current_experience;
    double accum_index;
    std::unordered_map<School, Level> level;

public:
    Summoner(size_t id, const std::string& name, size_t initiative, size_t max_hp,
             size_t max_energy, double accum_index = 1.0)
        : Entity(id, name, initiative, max_hp),
          energy(max_energy),
          max_energy(max_energy),
          current_experience(0),
          accum_index(accum_index) {}

    size_t getEnergy() const { return energy; }
    const std::unordered_map<School, Level>& getLevel() const { return level; }

    void accum_energy() {
        energy = std::min(energy + 1, max_energy);
    }

    void upgrade(School school) {
        auto it = level.find(school);
        if (it == level.end()) {
            level[school] = Level(0, current_experience);
        } else {
            level[school].upgrade(current_experience);
        }
    }
};

#endif // SUMMONER_HPP
