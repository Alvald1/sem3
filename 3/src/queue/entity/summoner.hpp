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
        if (max_energy == 0) {
            throw std::invalid_argument("Maximum energy cannot be zero");
        }
        if (accum_index == 0) {
            throw std::invalid_argument("Accumulation index cannot be zero");
        }

        const auto& school_list = schools.get_schools();
        level.reserve(school_list.size());
        for (const auto& school : school_list) {
            level.emplace(school.get_id(), 1);
        }
    }

    // Delete move operations since base class Entity has deleted them
    Summoner(Summoner&&) noexcept = default;
    Summoner& operator=(Summoner&&) noexcept = delete;

    // Optimize getters with noexcept
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
        return level.contains(school_id) ? level.at(school_id) : 0;
    }

    [[nodiscard]] bool
    has_enough_energy(size_t required_energy) const noexcept {
        return energy >= required_energy;
    }

    [[nodiscard]] bool
    can_level_up(size_t school_id, size_t required_exp) const noexcept {
        return current_experience >= required_exp && level.contains(school_id);
    }

    void
    add_experience(size_t exp) noexcept {
        if (exp > 0) {
            // Проверка на переполнение
            if (current_experience > SIZE_MAX - exp) {
                current_experience = SIZE_MAX;
            } else {
                current_experience += exp;
            }
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
        // Проверка на переполнение
        if (accum_index > SIZE_MAX - energy) {
            energy = max_energy;
        } else {
            energy = std::min(energy + accum_index, max_energy);
        }
    }

    void
    reset_energy() noexcept {
        energy = max_energy;
    }

    void
    upgrade(size_t school_id) {
        auto it = level.find(school_id);
        if (it == level.end()) {
            throw std::invalid_argument("Invalid school ID: " + std::to_string(school_id));
        }
        ++it->second;
    }

    [[nodiscard]] const std::unordered_map<size_t, size_t>&
    get_level() const noexcept {
        return level;
    }
};

#endif // SUMMONER_HPP
