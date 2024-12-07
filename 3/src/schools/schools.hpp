#ifndef SCHOOLS_HPP
#define SCHOOLS_HPP

#include <unordered_map>
#include <vector>
#include "school/ability/ability.hpp"
#include "school/school.hpp"

class Schools {
  private:
    std::vector<School> schools;

  public:
    // Constructors and assignment operators
    Schools() = default;
    Schools(const Schools&) = default;
    Schools(Schools&&) noexcept = default;
    Schools& operator=(const Schools&) = default;
    Schools& operator=(Schools&&) noexcept = default;

    // Existing methods
    void add_school(School school);
    size_t count_schools() const;
    size_t count_creatures() const;
    std::vector<Ability> get_available_abilities(std::unordered_map<School, size_t> levels) const;
    std::vector<Ability> get_upgradable_abilities(size_t exp, std::unordered_map<School, size_t> levels) const;

    // New methods
    const School* find_school_by_id(size_t id) const;
    const School* find_school_by_name(const std::string& name) const;
    size_t count_total_abilities() const;

    const std::vector<School>&
    get_schools() const {
        return schools;
    }

    bool has_school(size_t id) const;
    bool remove_school(size_t id);
};

#endif // SCHOOLS_HPP
