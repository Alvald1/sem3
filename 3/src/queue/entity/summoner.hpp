#ifndef SUMMONER_HPP
#define SUMMONER_HPP

#include <cstddef>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "entity.hpp"
#include "schools/school/school.hpp"
#include "schools/schools.hpp"
#include "utilities/exceptions.hpp"

/**
 * @brief Class representing a Summoner entity in the game
 * 
 * Summoner is a special type of Entity that can accumulate energy, gain experience,
 * and level up in different schools of magic.
 */
class Summoner : public Entity {
    friend class SummonerBuilder;

  private:
    /// Current energy level of the summoner
    size_t energy;
    /// Maximum energy capacity
    size_t max_energy;
    /// Current experience points
    size_t current_experience;
    /// Energy accumulation rate
    size_t accum_index;
    /// Map of school IDs to their corresponding levels
    std::unordered_map<size_t, size_t> levels;
    /// List of owned entity IDs
    std::vector<size_t> ownerships;

    /**
     * @brief Private constructor for Summoner
     * @param ability Initial ability of the summoner
     */
    explicit Summoner(const Ability& ability) : Entity(ability), current_experience(0) {
        const auto& school_list = Schools::getInstance().get_schools();
        levels.reserve(school_list.size());
        for (const auto& school : school_list) {
            levels.emplace(school.get_id(), 1);
        }
    }

    // Optimize getters with noexcept
  public:
    // Rule of five
    Summoner(const Summoner&) = default;
    Summoner& operator=(const Summoner&) = delete; // Due to const members
    Summoner(Summoner&&) noexcept = default;
    Summoner& operator=(Summoner&&) = delete; // Due to const members
    ~Summoner() override = default;

    /**
     * @brief Get current energy level
     * @return Current energy amount
     */
    [[nodiscard]] size_t
    get_energy() const noexcept {
        return energy;
    }

    /**
     * @brief Get current experience points
     * @return Current experience amount
     */
    [[nodiscard]] size_t
    get_experience() const noexcept {
        return current_experience;
    }

    /**
     * @brief Get maximum energy capacity
     * @return Maximum energy amount
     */
    [[nodiscard]] size_t
    get_max_energy() const noexcept {
        return max_energy;
    }

    /**
     * @brief Get energy accumulation rate
     * @return Energy accumulation index
     */
    [[nodiscard]] size_t
    get_accum_index() const noexcept {
        return accum_index;
    }

    /**
     * @brief Get level in specific school
     * @param school_id ID of the school
     * @return Level in the specified school, 0 if school not found
     */
    [[nodiscard]] size_t
    get_school_level(size_t school_id) const noexcept {
        return levels.find(school_id) != levels.end() ? levels.at(school_id) : 0;
    }

    /**
     * @brief Add experience points
     * @param exp Amount of experience to add
     */
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

    /**
     * @brief Spend energy
     * @param amount Amount of energy to spend
     * @throw NotEnoughEnergyException if not enough energy available
     */
    void
    spend_energy(size_t amount) {
        if (amount == 0) {
            return;
        }
        if (amount > energy) {
            throw NotEnoughEnergyException(energy, amount);
        }
        energy -= amount;
    }

    /**
     * @brief Accumulate energy according to accumulation index
     */
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

    /**
     * @brief Reset energy to maximum capacity
     */
    void
    reset_energy() noexcept {
        energy = max_energy;
    }

    /**
     * @brief Add energy amount
     * @param amount Amount of energy to add
     */
    void
    add_energy(size_t amount) noexcept {
        if (energy > max_energy - amount) {
            energy = max_energy;
        } else {
            energy += amount;
        }
    }

    /**
     * @brief Upgrade level in specific school
     * @param school School to upgrade
     * @param required_exp Experience required for upgrade
     * @throw NotEnoughExperienceException if not enough experience
     * @throw std::invalid_argument if school ID is invalid
     */
    void
    upgrade_school(const School& school, size_t required_exp) {
        if (current_experience < required_exp) {
            throw NotEnoughExperienceException(current_experience, required_exp);
        }

        auto it = levels.find(school.get_id());
        if (it == levels.end()) {
            throw std::invalid_argument("Invalid school ID: " + std::to_string(school.get_id()));
        }

        current_experience -= required_exp;
        ++it->second;
    }

    /**
     * @brief Add entity to ownerships
     * @param entity_id ID of entity to add
     */
    void
    add_ownership(size_t entity_id) {
        ownerships.push_back(entity_id);
    }

    /**
     * @brief Remove entity from ownerships
     * @param entity_id ID of entity to remove
     */
    void
    delete_ownership(size_t entity_id) {
        std::erase(ownerships, entity_id);
    }

    /**
     * @brief Get list of owned entity IDs
     * @return Const reference to ownerships vector
     */
    [[nodiscard]] const std::vector<size_t>&
    get_ownerships() const noexcept {
        return ownerships;
    }

    /**
     * @brief Get map of school levels
     * @return Const reference to levels map
     */
    [[nodiscard]] const std::unordered_map<size_t, size_t>&
    get_levels() const noexcept {
        return levels;
    }

    /**
     * @brief Get mutable map of school levels
     * @return Reference to levels map
     */
    [[nodiscard]] std::unordered_map<size_t, size_t>&
    get_levels_mutable() noexcept {
        return levels;
    }
};

#endif // SUMMONER_HPP
