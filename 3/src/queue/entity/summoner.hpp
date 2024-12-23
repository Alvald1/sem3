#ifndef SUMMONER_HPP
#define SUMMONER_HPP

#include <cstddef>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "entity.hpp"
#include "src/schools/school/school.hpp"
#include "src/schools/schools.hpp"

class Summoner : public Entity {
    friend class SummonerBuilder;

  private:
    size_t energy;
    const size_t max_energy;
    size_t current_experience;
    size_t accum_index;
    std::unordered_map<size_t, size_t> levels;

    explicit Summoner(const Ability& ability, size_t max_energy, size_t accum_index = 1)
        : Entity(ability), energy(max_energy), max_energy(max_energy), current_experience(0), accum_index(accum_index) {
        if (max_energy == 0) {
            throw std::invalid_argument("Maximum energy cannot be zero");
        }
        if (accum_index == 0) {
            throw std::invalid_argument("Accumulation index cannot be zero");
        }

        const auto& school_list = Schools::getInstance().get_schools();
        levels.reserve(school_list.size());
        for (const auto& school : school_list) {
            levels.emplace(school.get_id(), 1);
        }
    }

    // Optimize getters with noexcept
  public:
    [[nodiscard]] size_t
    get_energy() const noexcept {
        return energy;
    }

    [[nodiscard]] size_t
    get_experience() const noexcept {
        return current_experience;
    }

    [[nodiscard]] size_t
    get_max_energy() const noexcept {
        return max_energy;
    }

    [[nodiscard]] size_t
    get_accum_index() const noexcept {
        return accum_index;
    }

    [[nodiscard]] size_t
    get_school_level(size_t school_id) const noexcept {
        return levels.find(school_id) != levels.end() ? levels.at(school_id) : 0;
    }

    void
    add_experience(size_t exp) noexcept {
        if (exp == 0) {
            return;
        }

        if (current_experience > std::numeric_limits<size_t>::max() - exp) {
            current_experience = std::numeric_limits<size_t>::max();
        } else {
            current_experience += exp;
        }
    }

    void
    spend_energy(size_t amount) {
        if (amount == 0) {
            return;
        }
        if (amount > energy) {
            throw std::runtime_error("Not enough energy: have " + std::to_string(energy) + ", need "
                                     + std::to_string(amount));
        }
        energy -= amount;
    }

    void
    accum_energy() noexcept {
        if (energy >= max_energy) {
            return;
        }

        if (max_energy - energy >= accum_index) {
            energy += accum_index;
        } else {
            energy = max_energy;
        }
    }

    void
    reset_energy() noexcept {
        energy = max_energy;
    }

    void
    upgrade(size_t school_id) {
        auto it = levels.find(school_id);
        if (it == levels.end()) {
            throw std::invalid_argument("Invalid school ID: " + std::to_string(school_id));
        }
        ++it->second;
    }

    [[nodiscard]] const std::unordered_map<size_t, size_t>&
    get_levels() const noexcept {
        return levels;
    }
};

#endif // SUMMONER_HPP
