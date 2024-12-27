#include <gtest/gtest.h>

#include "schools/builders/director.hpp"
#include "schools/school/school.hpp"

class SchoolTest : public ::testing::Test {
  protected:
    Creature test_creature = Director::buildCreature("Test Creature", 5, 10, 2, 1, 3);
    Ability test_ability = Director::buildAbility("Test Ability", test_creature, 1, 50, 100, 200);
    School default_school = Director::buildSchool("Test School", test_ability);
};

TEST_F(SchoolTest, CreationWithValidParameters) {
    EXPECT_EQ(default_school.get_name(), "Test School");
    EXPECT_EQ(default_school.get_abilities().size(), 1);
}

TEST_F(SchoolTest, AddAbility) {
    School school("New School");
    Creature creature2 = Director::buildCreature("Creature 2", 1, 1, 1, 1, 1);
    Ability ability2 = Director::buildAbility("Ability 2", creature2, 2, 60, 120, 250);

    school.add_ability(test_ability);
    school.add_ability(ability2);

    EXPECT_EQ(school.get_abilities().size(), 2);
    EXPECT_TRUE(school.has_ability(test_ability.get_id()));
    EXPECT_TRUE(school.has_ability(ability2.get_id()));
}

TEST_F(SchoolTest, GetAvailableAbilities) {
    School school("Test School");

    // Add regular ability
    school.add_ability(test_ability);

    // Add high-level ability
    Ability high_level_ability = Director::buildAbility("High Level", test_creature, 5, 100, 200, 300);
    school.add_ability(high_level_ability);

    auto available = school.get_available_abilities(1, 100);
    EXPECT_EQ(available.size(), 1);

    available = school.get_available_abilities(5, 100);
    EXPECT_EQ(available.size(), 2);
}

TEST_F(SchoolTest, GetUpgradableAbilities) {
    School school("Test School");
    school.add_ability(test_ability);

    auto upgradable = school.get_upgradable_abilities(1, 100);
    EXPECT_EQ(upgradable.size(), 1);

    upgradable = school.get_upgradable_abilities(1, 99);
    EXPECT_EQ(upgradable.size(), 0);
}

TEST_F(SchoolTest, FindAbilityById) {
    auto found_ability = default_school.find_ability_by_id(test_ability.get_id());
    EXPECT_TRUE(found_ability.has_value());
    EXPECT_EQ(found_ability->get_name(), test_ability.get_name());

    auto not_found = default_school.find_ability_by_id(999);
    EXPECT_FALSE(not_found.has_value());
}
