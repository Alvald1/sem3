#include <gtest/gtest.h>
#include "schools/school/ability/creature.hpp"

class CreatureTest : public ::testing::Test {
  protected:
    Creature default_creature{"Default"};
    Creature custom_creature{"Custom", 5, 10, 2, 1, 3};
};

// Constructor tests
TEST_F(CreatureTest, DefaultConstructor) {
    EXPECT_EQ(default_creature.get_name(), "Default");
    EXPECT_EQ(default_creature.get_speed(), 0);
    EXPECT_EQ(default_creature.get_damage(), 0);
    EXPECT_EQ(default_creature.get_range(), 0);
    EXPECT_EQ(default_creature.get_type(), 0);
    EXPECT_EQ(default_creature.get_initiative(), 0);
}

TEST_F(CreatureTest, CustomConstructor) {
    EXPECT_EQ(custom_creature.get_name(), "Custom");
    EXPECT_EQ(custom_creature.get_speed(), 5);
    EXPECT_EQ(custom_creature.get_damage(), 10);
    EXPECT_EQ(custom_creature.get_range(), 2);
    EXPECT_EQ(custom_creature.get_type(), 1);
    EXPECT_EQ(custom_creature.get_initiative(), 3);
}

// Copy constructor and assignment tests
TEST_F(CreatureTest, CopyConstructor) {
    Creature copied(custom_creature);
    EXPECT_EQ(copied.get_name(), custom_creature.get_name());
    EXPECT_EQ(copied.get_speed(), custom_creature.get_speed());
    EXPECT_EQ(copied.get_damage(), custom_creature.get_damage());
    EXPECT_EQ(copied.get_range(), custom_creature.get_range());
    EXPECT_EQ(copied.get_type(), custom_creature.get_type());
    EXPECT_EQ(copied.get_initiative(), custom_creature.get_initiative());
}

TEST_F(CreatureTest, CopyAssignment) {
    Creature assigned{"Temp"};
    assigned = custom_creature;
    EXPECT_EQ(assigned.get_name(), custom_creature.get_name());
    EXPECT_EQ(assigned.get_speed(), custom_creature.get_speed());
    EXPECT_EQ(assigned.get_damage(), custom_creature.get_damage());
    EXPECT_EQ(assigned.get_range(), custom_creature.get_range());
    EXPECT_EQ(assigned.get_type(), custom_creature.get_type());
    EXPECT_EQ(assigned.get_initiative(), custom_creature.get_initiative());
}

// Move constructor and assignment tests
TEST_F(CreatureTest, MoveConstructor) {
    Creature movable{"Movable", 5, 10, 2, 1, 3};
    Creature moved(std::move(movable));
    EXPECT_EQ(moved.get_name(), "Movable");
    EXPECT_EQ(moved.get_speed(), 5);
    EXPECT_EQ(moved.get_damage(), 10);
    EXPECT_EQ(moved.get_range(), 2);
    EXPECT_EQ(moved.get_type(), 1);
    EXPECT_EQ(moved.get_initiative(), 3);
}

TEST_F(CreatureTest, MoveAssignment) {
    Creature movable{"Movable", 5, 10, 2, 1, 3};
    Creature moved{"Temp"};
    moved = std::move(movable);
    EXPECT_EQ(moved.get_name(), "Movable");
    EXPECT_EQ(moved.get_speed(), 5);
    EXPECT_EQ(moved.get_damage(), 10);
    EXPECT_EQ(moved.get_range(), 2);
    EXPECT_EQ(moved.get_type(), 1);
    EXPECT_EQ(moved.get_initiative(), 3);
}

// Setter tests
TEST_F(CreatureTest, Setters) {
    default_creature.set_speed(5);
    EXPECT_EQ(default_creature.get_speed(), 5);

    default_creature.set_damage(10);
    EXPECT_EQ(default_creature.get_damage(), 10);

    default_creature.set_range(2);
    EXPECT_EQ(default_creature.get_range(), 2);

    default_creature.set_type(1);
    EXPECT_EQ(default_creature.get_type(), 1);

    default_creature.set_initiative(3);
    EXPECT_EQ(default_creature.get_initiative(), 3);
}

// ID increment test
TEST_F(CreatureTest, UniqueIDIncrement) {
    Creature first{"First"};
    Creature second{"Second"};
    EXPECT_EQ(second.get_id(), first.get_id() + 1);
}
