#include <gtest/gtest.h>

#include "schools/builders/director.hpp"
#include "schools/school/ability/creature.hpp"

class CreatureTest : public ::testing::Test {
  protected:
    Creature default_creature = Director::buildCreature("Test Creature", 5, 10, 2, 1, 3);
};

TEST_F(CreatureTest, CreationWithValidParameters) {
    EXPECT_EQ(default_creature.get_name(), "Test Creature");
    EXPECT_EQ(default_creature.get_speed(), 5);
    EXPECT_EQ(default_creature.get_damage(), 10);
    EXPECT_EQ(default_creature.get_range(), 2);
    EXPECT_EQ(default_creature.get_type(), 1);
    EXPECT_EQ(default_creature.get_initiative(), 3);
}

TEST_F(CreatureTest, ComparisonOperator) {
    auto creature1 = Director::buildCreature("Creature 1", 1, 1, 1, 1, 1);
    auto creature2 = Director::buildCreature("Creature 2", 2, 2, 2, 2, 2);

    EXPECT_TRUE(creature1 < creature2);
    EXPECT_FALSE(creature2 < creature1);
}

TEST_F(CreatureTest, ModifyingParameters) {
    Creature creature = Director::buildCreature("Modifiable Creature", 1, 1, 1, 1, 1);

    creature.set_speed(10);
    creature.set_damage(20);
    creature.set_range(3);
    creature.set_type(2);
    creature.set_initiative(5);

    EXPECT_EQ(creature.get_speed(), 10);
    EXPECT_EQ(creature.get_damage(), 20);
    EXPECT_EQ(creature.get_range(), 3);
    EXPECT_EQ(creature.get_type(), 2);
    EXPECT_EQ(creature.get_initiative(), 5);
}
