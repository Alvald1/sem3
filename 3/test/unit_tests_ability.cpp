#include <gtest/gtest.h>

#include "schools/builders/director.hpp"
#include "schools/school/ability/ability.hpp"

class AbilityTest : public ::testing::Test {
  protected:
    // Using data from Biomancy school
    Creature creature = Director::buildCreature("Master Geneticist", 0, 2, 3, 13, 0);
    Ability ability = Director::buildAbility("Bio-Engineer", creature, 0, 0, 0, 0);
};

TEST_F(AbilityTest, Construction) {
    EXPECT_EQ(ability.get_name(), "Bio-Engineer");
    EXPECT_EQ(ability.get_creature().get_name(), "Master Geneticist");
    EXPECT_EQ(ability.get_level(), 0);
    EXPECT_EQ(ability.get_energy(), 0);
    EXPECT_EQ(ability.get_experience(), 0);
    EXPECT_EQ(ability.get_hp(), 0);
}

TEST_F(AbilityTest, Setters) {
    // Using values from Biomancy's Bio-Engineer
    ability.set_level(1);
    ability.set_energy(10);
    ability.set_experience(100);
    ability.set_hp(15);

    EXPECT_EQ(ability.get_level(), 1);
    EXPECT_EQ(ability.get_energy(), 10);
    EXPECT_EQ(ability.get_experience(), 100);
    EXPECT_EQ(ability.get_hp(), 15);
}

TEST_F(AbilityTest, CanUpgrade) {
    ability.set_level(3);
    ability.set_experience(100);

    EXPECT_TRUE(ability.can_upgrade(100, 3));
    EXPECT_TRUE(ability.can_upgrade(150, 4));
    EXPECT_FALSE(ability.can_upgrade(50, 3));
    EXPECT_FALSE(ability.can_upgrade(100, 2));
}

TEST_F(AbilityTest, CreatureModification) {
    Creature creature = Director::buildCreature("Master Geneticist", 0, 2, 3, 18, 0);
    ability.set_creature(creature);

    EXPECT_EQ(ability.get_creature().get_name(), "Master Geneticist");
    EXPECT_EQ(ability.get_creature().get_type(), 18);
}
