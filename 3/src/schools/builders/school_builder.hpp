#ifndef SCHOOL_BUILDER_HPP
#define SCHOOL_BUILDER_HPP

#include "schools/school/ability/ability.hpp"
#include "schools/school/school.hpp"

class SchoolBuilder {
  private:
    School school;

  public:
    explicit SchoolBuilder(std::string name) : school(std::move(name)) {}

    SchoolBuilder&
    add_ability(Ability ability) {
        school.add_ability(std::move(ability));
        return *this;
    }

    [[nodiscard]] School
    build() const {
        return school;
    }
};

#endif // SCHOOL_BUILDER_HPP
