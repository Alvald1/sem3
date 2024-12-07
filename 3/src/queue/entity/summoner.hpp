#ifndef SUMMONER_HPP
#define SUMMONER_HPP

#include <unordered_map>
#include "../../schools/school/school.hpp"
#include "../../schools/schools.hpp"
#include "entity.hpp"

class Summoner : public Entity {
  private:
    size_t energy;
    const size_t max_energy;
    size_t current_experience;
    size_t accum_index;
    std::unordered_map<size_t, size_t> level;

  public:
    explicit Summoner(const Ability& ability, size_t max_energy, const Schools& schools, size_t accum_index = 1)
        : Entity(ability), energy(max_energy), max_energy(max_energy), current_experience(0), accum_index(accum_index) {
        // Initialize levels for all available schools to 1
        for (const auto& school : schools.get_schools()) {
            level[school.get_id()] = 1;
        }
    }

    size_t
    get_energy() const {
        return energy;
    }

    size_t
    get_experience() const {
        return current_experience;
    }

    size_t
    get_school_level(size_t school_id) const {
        auto it = level.find(school_id);
        return it != level.end() ? it->second : 0;
    }

    bool
    has_enough_energy(size_t required_energy) const {
        return energy >= required_energy;
    }

    void
    add_experience(size_t exp) {
        current_experience += exp;
    }

    void
    spend_energy(size_t amount) {
        if (amount > energy) {
            throw std::runtime_error("Not enough energy");
        }
        energy -= amount;
    }

    const std::unordered_map<size_t, size_t>&
    get_level() const {
        return level;
    }

    void
    accum_energy() {
        energy = std::min(energy + accum_index, max_energy);
    }

    void
    upgrade(size_t school_id) {
        ++level[school_id];
    }
};

#endif // SUMMONER_HPP
