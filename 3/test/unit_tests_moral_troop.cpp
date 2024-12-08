#include <gtest/gtest.h>
#include "../src/queue/entity/troop/moral_troop.hpp"
#include "../src/schools/school/ability/creature.hpp"

class MoralTroopTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a creature for testing
        creature = new Creature("TestCreature", 10, 5, 3, 2, 1);
        ability = new Ability("TestAbility", creature, 1, 100, 50, 20);
    }

    void TearDown() override {
        delete creature;
        delete ability;
    }

    Creature* creature;
    Ability* ability;
};

TEST_F(MoralTroopTest, Constructor) {
    MoralTroop troop(*ability);
    EXPECT_EQ(troop.get_moral(), 0);
}

TEST_F(MoralTroopTest, IncreaseMorale) {
    MoralTroop troop(*ability);
    troop.increase_morale();
    EXPECT_EQ(troop.get_moral(), 1);
    troop.increase_morale();
    EXPECT_EQ(troop.get_moral(), 2);
}

TEST_F(MoralTroopTest, DecreaseMorale) {
    MoralTroop troop(*ability);
    troop.decrease_morale();
    EXPECT_EQ(troop.get_moral(), -1);
    troop.decrease_morale();
    EXPECT_EQ(troop.get_moral(), -2);
}

TEST_F(MoralTroopTest, BalanceMoralePositive) {
    MoralTroop troop(*ability, 2);
    troop.balance_morale();
    EXPECT_EQ(troop.get_moral(), 1);
    troop.balance_morale();
    EXPECT_EQ(troop.get_moral(), 0);
}

TEST_F(MoralTroopTest, BalanceMoraleNegative) {
    MoralTroop troop(*ability, -2);
    troop.balance_morale();
    EXPECT_EQ(troop.get_moral(), -1);
    troop.balance_morale();
    EXPECT_EQ(troop.get_moral(), 0);
}

TEST_F(MoralTroopTest, BalanceMoraleZero) {
    MoralTroop troop(*ability, 0);
    troop.balance_morale();
    EXPECT_EQ(troop.get_moral(), 0);
}

TEST_F(MoralTroopTest, SetMoral) {
    MoralTroop troop(*ability);
    troop.set_moral(5);
    EXPECT_EQ(troop.get_moral(), 5);
    troop.set_moral(-3);
    EXPECT_EQ(troop.get_moral(), -3);
}

TEST_F(MoralTroopTest, InheritedProperties) {
    MoralTroop troop(*ability);
    EXPECT_EQ(troop.get_speed(), creature->get_speed());
    EXPECT_EQ(troop.get_damage(), creature->get_damage());
    EXPECT_EQ(troop.get_range(), creature->get_range());
    EXPECT_EQ(troop.get_type(), creature->get_type());
    EXPECT_EQ(troop.get_hp(), ability->get_count());
}

TEST_F(MoralTroopTest, ExtremeMoralValues) {
    MoralTroop troop(*ability);
    
    // Test extremely high moral
    troop.set_moral(INT_MAX);
    EXPECT_EQ(troop.get_moral(), INT_MAX);
    troop.increase_morale();
    EXPECT_EQ(troop.get_moral(), INT_MIN); // Should overflow

    // Test extremely low moral
    troop.set_moral(INT_MIN);
    EXPECT_EQ(troop.get_moral(), INT_MIN);
    troop.decrease_morale();
    EXPECT_EQ(troop.get_moral(), INT_MAX); // Should underflow
}

TEST_F(MoralTroopTest, NullCreatureInAbility) {
    try {
        Ability nullAbility("NullTest", nullptr);
        FAIL() << "Expected std::invalid_argument";
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ(e.what(), "Creature cannot be null");
    }
}

TEST_F(MoralTroopTest, ZeroHPTroop) {
    MoralTroop troop(*ability);
    troop.set_hp(0);
    EXPECT_FALSE(troop.is_alive());
    
    // Check that moral changes still work on dead troop
    troop.increase_morale();
    EXPECT_EQ(troop.get_moral(), 1);
    troop.decrease_morale();
    EXPECT_EQ(troop.get_moral(), 0);
}

TEST_F(MoralTroopTest, MaxHPTroop) {
    MoralTroop troop(*ability);
    size_t max_hp = troop.get_max_hp();
    
    // Try to set HP above max
    troop.set_hp(max_hp + 100);
    EXPECT_EQ(troop.get_hp(), max_hp);
    
    // Verify heal doesn't exceed max HP
    troop.do_damage(10);
    troop.heal(100);
    EXPECT_EQ(troop.get_hp(), max_hp);
}

TEST_F(MoralTroopTest, ConsecutiveMoraleChanges) {
    MoralTroop troop(*ability);
    
    // Multiple increases followed by multiple decreases
    for(int i = 0; i < 1000; ++i) {
        troop.increase_morale();
    }
    for(int i = 0; i < 2000; ++i) {
        troop.decrease_morale();
    }
    EXPECT_EQ(troop.get_moral(), -1000);
}

TEST_F(MoralTroopTest, BalanceMoraleExtremeCases) {
    MoralTroop troop(*ability);
    
    // Test balance from extreme positive
    troop.set_moral(INT_MAX);
    troop.balance_morale();
    EXPECT_EQ(troop.get_moral(), INT_MAX - 1);
    
    // Test balance from extreme negative
    troop.set_moral(INT_MIN);
    troop.balance_morale();
    EXPECT_EQ(troop.get_moral(), INT_MIN + 1);
}
