#ifndef SCHOOLS_HPP
#define SCHOOLS_HPP

#include <optional>
#include <unordered_map>
#include <vector>

#include "school/ability/ability.hpp"
#include "school/school.hpp"

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

    static Schools&
    getInstance() {
        if (instance_ == nullptr) {
            instance_ = new Schools();
        }
        return *instance_;
    }

    // Existing methods
    void add_school(School school);
    size_t count_schools() const;
    size_t count_creatures() const;
    std::vector<std::reference_wrapper<const Ability>>
    get_available_abilities(const std::unordered_map<size_t, size_t>& levels, size_t energy) const;
    std::vector<std::reference_wrapper<const Ability>>
    get_upgradable_abilities(const std::unordered_map<size_t, size_t>& levels, size_t exp) const;

    // New methods
    std::optional<std::reference_wrapper<const School>> find_school_by_id(size_t id) const;
    std::optional<std::reference_wrapper<const School>> find_school_by_name(const std::string& name) const;
    size_t count_total_abilities() const;
    std::optional<std::reference_wrapper<const School>> find_school_by_ability_id(size_t ability_id) const;

    const std::vector<School>&
    get_schools() const {
        return schools;
    }

    bool has_school(size_t id) const;
    bool remove_school(size_t id);
};

#endif // SCHOOLS_HPP
