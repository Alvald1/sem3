#ifndef SCHOOL_HPP
#define SCHOOL_HPP

#include <functional>
#include <memory>
#include <optional>
#include <set>
#include <vector>

#include "ability/ability.hpp"
#include "utilities/name_id.hpp"

/**
 * @brief Represents a magic school containing abilities
 * 
 * Each school has a unique ID, name, and collection of abilities.
 * Inherits from NameID for basic identification functionality.
 */
class School : public NameID {
  private:
    static inline size_t next_id = 1;
    std::vector<Ability> abilities;

  public:
    /**
     * @brief Construct a new School
     * @param name Name of the school
     */
    explicit School(std::string name) : NameID(next_id++, std::move(name)) {}

    School(const School&) = default;
    School(School&&) noexcept = default;
    School& operator=(const School&) = default;
    School& operator=(School&&) noexcept = default;

    /**
     * @brief Add new ability to the school
     * @param ability Ability to add
     */
    void add_ability(Ability ability);

    /**
     * @brief Get abilities available at given level and energy
     * @param level Current level
     * @param energy Available energy
     * @return Vector of available abilities
     */
    std::vector<std::reference_wrapper<const Ability>> get_available_abilities(size_t level, size_t energy) const;

    /**
     * @brief Gets abilities that can be upgraded
     * @param level Current level
     * @param exp Available experience points
     * @return Vector of references to upgradable abilities
     */
    std::vector<std::reference_wrapper<const Ability>> get_upgradable_abilities(size_t level, size_t exp) const;

    std::optional<Ability> find_ability_by_id(size_t id) const;
    bool has_ability(size_t id) const;

    [[nodiscard]] size_t count_creatures() const;

    const std::vector<Ability>&
    get_abilities() const {
        return abilities;
    }
};

#endif // SCHOOL_HPP
