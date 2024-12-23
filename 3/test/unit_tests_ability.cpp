#include <gtest/gtest.h>
#include "schools/school/ability/ability.hpp"

// Mock Creature class for testing
class MockCreature : public Creature {
  public:
    MockCreature() : Creature("MockCreature") {}
};

class AbilityTest : public ::testing::Test {
  protected:
    MockCreature* creature;

    void
    SetUp() override {
        creature = new MockCreature();
    }

    void
    TearDown() override {
        delete creature;
    }
};

// Constructor tests
TEST_F(AbilityTest, ConstructorValidInput) {
    Ability ability("TestAbility", creature, 1, 100, 50, 2);
    EXPECT_EQ(ability.get_name(), "TestAbility");
    EXPECT_EQ(ability.get_creature(), creature);
    EXPECT_EQ(ability.get_level(), 1);
    EXPECT_EQ(ability.get_energy(), 100);
    EXPECT_EQ(ability.get_experience(), 50);
    EXPECT_EQ(ability.get_count(), 2);
}

TEST_F(AbilityTest, ConstructorNullCreature) { EXPECT_THROW(Ability("TestAbility", nullptr), std::invalid_argument); }

// Getter tests
TEST_F(AbilityTest, Getters) {
    Ability ability("TestAbility", creature, 1, 100, 50, 2);
    EXPECT_EQ(ability.get_creature(), creature);
    EXPECT_EQ(ability.get_level(), 1);
    EXPECT_EQ(ability.get_energy(), 100);
    EXPECT_EQ(ability.get_experience(), 50);
    EXPECT_EQ(ability.get_count(), 2);
}

// Setter tests
TEST_F(AbilityTest, Setters) {
    Ability ability("TestAbility", creature);
    MockCreature* new_creature = new MockCreature();

    ability.set_creature(new_creature);
    ability.set_level(2);
    ability.set_energy(200);
    ability.set_experience(100);
    ability.set_count(3);

    EXPECT_EQ(ability.get_creature(), new_creature);
    EXPECT_EQ(ability.get_level(), 2);
    EXPECT_EQ(ability.get_energy(), 200);
    EXPECT_EQ(ability.get_experience(), 100);
    EXPECT_EQ(ability.get_count(), 3);

    delete new_creature;
}

TEST_F(AbilityTest, SetterNullCreature) {
    Ability ability("TestAbility", creature);
    EXPECT_THROW(ability.set_creature(nullptr), std::invalid_argument);
}

// Utility method tests
TEST_F(AbilityTest, CanUpgrade) {
    Ability ability("TestAbility", creature, 2, 100, 50, 1);

    EXPECT_TRUE(ability.can_upgrade(50, 2));
    EXPECT_TRUE(ability.can_upgrade(100, 3));
    EXPECT_FALSE(ability.can_upgrade(49, 2));
    EXPECT_FALSE(ability.can_upgrade(50, 1));
}

TEST_F(AbilityTest, HasCreature) {
    Ability ability("TestAbility", creature);
    EXPECT_TRUE(ability.has_creature());

    MockCreature* another_creature = new MockCreature();
    ability.set_creature(another_creature);
    EXPECT_TRUE(ability.has_creature());
    delete another_creature;
}

// Copy and move tests
TEST_F(AbilityTest, CopyConstructor) {
    Ability original("TestAbility", creature, 1, 100, 50, 2);
    Ability copy(original);

    EXPECT_EQ(copy.get_name(), original.get_name());
    EXPECT_EQ(copy.get_creature(), original.get_creature());
    EXPECT_EQ(copy.get_level(), original.get_level());
    EXPECT_EQ(copy.get_energy(), original.get_energy());
    EXPECT_EQ(copy.get_experience(), original.get_experience());
    EXPECT_EQ(copy.get_count(), original.get_count());
}

TEST_F(AbilityTest, CopyAssignment) {
    Ability original("TestAbility", creature, 1, 100, 50, 2);
    Ability copy("OtherAbility", creature);

    copy = original;

    EXPECT_EQ(copy.get_name(), original.get_name());
    EXPECT_EQ(copy.get_creature(), original.get_creature());
    EXPECT_EQ(copy.get_level(), original.get_level());
    EXPECT_EQ(copy.get_energy(), original.get_energy());
    EXPECT_EQ(copy.get_experience(), original.get_experience());
    EXPECT_EQ(copy.get_count(), original.get_count());
}

TEST_F(AbilityTest, MoveAssignment) {
    Ability original("TestAbility", creature, 1, 100, 50, 2);
    Ability moved("OtherAbility", creature);

    moved = std::move(original);

    EXPECT_EQ(moved.get_name(), "TestAbility");
    EXPECT_EQ(moved.get_creature(), creature);
    EXPECT_EQ(moved.get_level(), 1);
    EXPECT_EQ(moved.get_energy(), 100);
    EXPECT_EQ(moved.get_experience(), 50);
    EXPECT_EQ(moved.get_count(), 2);
}
