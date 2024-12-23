#ifndef SCHOOL_BUILDER_HPP
#define SCHOOL_BUILDER_HPP

#include <string>
#include "schools/school/ability/ability.hpp"

class School;

class SchoolBuilder {
  public:
    explicit SchoolBuilder(std::string name);
    SchoolBuilder& addAbility(Ability ability);
    School build();

  private:
    School* school_;
};

#endif // SCHOOL_BUILDER_HPP
