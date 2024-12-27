#include <gtest/gtest.h>
#include "queue/entity/builder/entity_director.hpp"
#include "schools/builders/director.hpp"

class TroopTest : public ::testing::Test {
  protected:
    Creature test_creature = Director::buildCreature("TestCreature", 5, 5, 3, 1, 10);
    Ability test_ability = Director::buildAbility("TestTroop", test_creature, 1, 0, 0, 1000);
    MoralTroop* moral_troop{nullptr};
    AmoralTroop* amoral_troop{nullptr};

    void
    SetUp() override {
        moral_troop = new MoralTroop(EntityDirector::createMoralTroop(test_ability, 50, 1));
        amoral_troop = new AmoralTroop(EntityDirector::createAmoralTroop(test_ability, 1));
    }

    void
    TearDown() override {
        delete moral_troop;
        moral_troop = nullptr;
        delete amoral_troop;
        amoral_troop = nullptr;
    }

    ~TroopTest() override {
        if (moral_troop) {
            delete moral_troop;
            moral_troop = nullptr;
        }
        if (amoral_troop) {
            delete amoral_troop;
            amoral_troop = nullptr;
        }
    }
};

TEST_F(TroopTest, MoralTroopInitialization) {
    EXPECT_EQ(moral_troop->get_moral(), 50);
    EXPECT_EQ(moral_troop->get_speed(), 5);
    EXPECT_EQ(moral_troop->get_damage(), 5);
    EXPECT_EQ(moral_troop->get_range(), 3);
    EXPECT_EQ(moral_troop->get_id_summoner(), 1);
}

TEST_F(TroopTest, MoralTroopMoralModification) {
    moral_troop->increase_morale(25);
    EXPECT_EQ(moral_troop->get_moral(), 75);

    moral_troop->decrease_morale(50);
    EXPECT_EQ(moral_troop->get_moral(), 25);

    moral_troop->set_moral(-30);
    moral_troop->balance_morale(10);
    EXPECT_EQ(moral_troop->get_moral(), -20);
}

TEST_F(TroopTest, AmoralTroopInitialization) {
    EXPECT_EQ(amoral_troop->get_speed(), 5);
    EXPECT_EQ(amoral_troop->get_damage(), 5);
    EXPECT_EQ(amoral_troop->get_range(), 3);
    EXPECT_EQ(amoral_troop->get_id_summoner(), 1);
}

TEST_F(TroopTest, MovementMechanics) {
    EXPECT_EQ(moral_troop->get_remaining_movement(), 5);
    moral_troop->spend_movement(3);
    EXPECT_EQ(moral_troop->get_remaining_movement(), 2);

    moral_troop->reset_movement();
    EXPECT_EQ(moral_troop->get_remaining_movement(), 5);
}

TEST_F(TroopTest, StatModification) {
    moral_troop->modify_speed(2);
    EXPECT_EQ(moral_troop->get_speed(), 7);

    moral_troop->modify_damage(-3);
    EXPECT_EQ(moral_troop->get_damage(), 2);

    moral_troop->modify_range(1);
    EXPECT_EQ(moral_troop->get_range(), 4);
}
