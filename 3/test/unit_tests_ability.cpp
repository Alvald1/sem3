#include <gtest/gtest.h>

#include "schools/builders/director.hpp"
#include "schools/school/ability/ability.hpp"

class AbilityTest : public ::testing::Test {
  protected:
    Creature test_creature = Director::buildCreature("Test Creature", 5, 10, 2, 1, 3);
    Ability default_ability = Director::buildAbility("Test Ability", test_creature, 1, 50, 100, 200);
};

TEST_F(AbilityTest, CreationWithValidParameters) {
    EXPECT_EQ(default_ability.get_name(), "Test Ability");
    EXPECT_EQ(default_ability.get_level(), 1);
    EXPECT_EQ(default_ability.get_energy(), 50);
    EXPECT_EQ(default_ability.get_experience(), 100);
    EXPECT_EQ(default_ability.get_hp(), 200);
    EXPECT_EQ(default_ability.get_creature().get_name(), "Test Creature");
}

TEST_F(AbilityTest, CanUpgrade) {
    EXPECT_TRUE(default_ability.can_upgrade(100, 1));  // Exact match
    EXPECT_TRUE(default_ability.can_upgrade(150, 2));  // More than required
    EXPECT_FALSE(default_ability.can_upgrade(99, 1));  // Not enough experience
    EXPECT_FALSE(default_ability.can_upgrade(100, 0)); // Not enough level
}

TEST_F(AbilityTest, ModifyingParameters) {
    Ability ability = default_ability;
    Creature new_creature = Director::buildCreature("New Creature", 1, 1, 1, 1, 1);

    ability.set_level(2);
    ability.set_energy(75);
    ability.set_experience(150);
    ability.set_hp(300);
    ability.set_creature(new_creature);

    EXPECT_EQ(ability.get_level(), 2);
    EXPECT_EQ(ability.get_energy(), 75);
    EXPECT_EQ(ability.get_experience(), 150);
    EXPECT_EQ(ability.get_hp(), 300);
    EXPECT_EQ(ability.get_creature().get_name(), "New Creature");
}
