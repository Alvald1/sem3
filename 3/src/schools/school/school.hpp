#ifndef SCHOOL_HPP
#define SCHOOL_HPP

#include <optional>
#include <vector>
#include "../utilities/name_id.hpp"
#include "ability/ability.hpp"

class School : public NameID {
  private:
    static inline size_t next_id = 1;
    std::vector<Ability> abilities;

  public:
    explicit School(const std::string& name);
    School(const School&) = default;
    School(School&&) noexcept = default;
    School& operator=(const School&) = default;
    School& operator=(School&&) noexcept = default;

    void add_ability(const Ability& ability);
    const std::vector<Ability>& get_available_abilities(size_t level) const;
    const std::vector<Ability>& get_upgradable_abilities(size_t exp, size_t level) const;
    std::optional<const Ability&> find_ability_by_id(size_t id) const;
    bool has_ability(size_t id) const;

    const std::vector<Ability>&
    get_abilities() const {
        return abilities;
    }
};

#endif // SCHOOL_HPP
