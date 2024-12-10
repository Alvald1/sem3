#ifndef SCHOOL_HPP
#define SCHOOL_HPP

#include <optional>
#include <set>
#include <unordered_map>
#include <vector>
#include "../../utilities/name_id.hpp"
#include "ability/ability.hpp"

class School : public NameID {
  private:
    static inline size_t next_id = 1;
    std::vector<Ability> abilities;

  public:
    explicit School(const std::string& name) : NameID(next_id++, name) {}

    School(const School&) = default;
    School(School&&) noexcept = default;
    School& operator=(const School&) = default;
    School& operator=(School&&) noexcept = default;

    void add_ability(const Ability& ability);
    std::vector<Ability> get_available_abilities(size_t level, size_t energy) const;
    std::vector<Ability> get_upgradable_abilities(size_t level, size_t exp) const;
    std::optional<Ability> find_ability_by_id(size_t id) const;
    bool has_ability(size_t id) const;

    [[nodiscard]] size_t count_creatures() const;

    const std::vector<Ability>&
    get_abilities() const {
        return abilities;
    }
};

#endif // SCHOOL_HPP
