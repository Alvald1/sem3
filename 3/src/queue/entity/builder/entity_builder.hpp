#ifndef ENTITY_BUILDER_HPP
#define ENTITY_BUILDER_HPP

#include "../../../schools/school/ability/ability.hpp"
#include "../entity.hpp"

class EntityBuilder {
  protected:
    Ability ability;

  public:
    explicit EntityBuilder(const Ability& ability) : ability(ability) {}

    virtual ~EntityBuilder() = default;

    virtual void
    reset(const Ability& new_ability) {
        ability = new_ability;
    }

    [[nodiscard]] virtual Entity* build() = 0;
};

#endif // ENTITY_BUILDER_HPP
