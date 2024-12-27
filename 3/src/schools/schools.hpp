#ifndef SCHOOLS_HPP
#define SCHOOLS_HPP

#include <optional>
#include <unordered_map>
#include <vector>

#include "school/ability/ability.hpp"
#include "school/school.hpp"

/**
 * @brief Singleton class managing all magic schools
 * 
 * This class manages a collection of magic schools and provides methods
 * to access and manipulate them. Implements the Singleton pattern.
 */
class Schools {
  private:
    static Schools* instance_;
    std::vector<School> schools;

    // Private constructor
    Schools() = default;

  public:
    // Delete copy/move operations
    Schools(const Schools&) = delete;
    Schools(Schools&&) noexcept = delete;
    Schools& operator=(const Schools&) = delete;
    Schools& operator=(Schools&&) noexcept = delete;

    /**
     * @brief Get singleton instance
     * @return Reference to the singleton instance
     */
    static Schools&
    getInstance() {
        if (instance_ == nullptr) {
            instance_ = new Schools();
        }
        return *instance_;
    }

    /**
     * @brief Destroy singleton instance
     */
    static void
    destroyInstance() {
        delete instance_;
        instance_ = nullptr;
    }

    /**
     * @brief Adds a new school to the collection
     * @param school The school to be added
     */
    void add_school(School school);

    /**
     * @brief Counts the total number of schools
     * @return Number of schools in the collection
     */
    [[nodiscard]] size_t count_schools() const;

    /**
     * @brief Counts unique creatures across all schools
     * @return Number of unique creatures
     */
    [[nodiscard]] size_t count_creatures() const;

    /**
     * @brief Gets abilities available based on levels and energy
     * @param levels Map of school IDs to their levels
     * @param energy Available energy
     * @return Vector of references to available abilities
     */
    [[nodiscard]] std::vector<std::reference_wrapper<const Ability>>
    get_available_abilities(const std::unordered_map<size_t, size_t>& levels, size_t energy) const;

    /**
     * @brief Gets abilities that can be upgraded
     * @param levels Map of school IDs to their levels
     * @param exp Available experience points
     * @return Vector of references to upgradable abilities
     */
    [[nodiscard]] std::vector<std::reference_wrapper<const Ability>>
    get_upgradable_abilities(const std::unordered_map<size_t, size_t>& levels, size_t exp) const;

    /**
     * @brief Finds a school by its ID
     * @param id School identifier
     * @return Optional reference to the found school
     */
    [[nodiscard]] std::optional<std::reference_wrapper<const School>> find_school_by_id(size_t id) const;

    /**
     * @brief Find a school by name
     * @param name School name to search for
     * @return Optional reference to the found school
     */
    std::optional<std::reference_wrapper<const School>> find_school_by_name(const std::string& name) const;

    /**
     * @brief Get total number of abilities across all schools
     * @return Number of abilities
     */
    size_t count_total_abilities() const;

    /**
     * @brief Find a school by an ability ID
     * @param ability_id Ability ID to search for
     * @return Optional reference to the found school
     */
    std::optional<std::reference_wrapper<const School>> find_school_by_ability_id(size_t ability_id) const;

    /**
     * @brief Get abilities related to summoning
     * @return Vector of summoner abilities
     */
    std::vector<std::reference_wrapper<const Ability>> find_summoner_abilities() const;

    /**
     * @brief Get all schools
     * @return Vector of schools
     */
    const std::vector<School>&
    get_schools() const {
        return schools;
    }

    /**
     * @brief Check if a school exists by its ID
     * @param id School ID to check
     * @return True if the school exists, false otherwise
     */
    bool has_school(size_t id) const;

    /**
     * @brief Remove a school by its ID
     * @param id School ID to remove
     * @return True if the school was removed, false otherwise
     */
    bool remove_school(size_t id);
};

#endif // SCHOOLS_HPP
