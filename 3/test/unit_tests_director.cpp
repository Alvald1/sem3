#include <gtest/gtest.h>
#include "queue/entity/builder/entity_director.hpp"
#include "schools/builders/director.hpp"

class DirectorTest : public ::testing::Test {
  protected:
    Creature test_creature = Director::buildCreature("TestCreature", 5, 5, 3, 1, 10);
    Ability test_ability = Director::buildAbility("TestAbility", test_creature, 1, 50, 100, 1000);
};

TEST_F(DirectorTest, CreatureBuilding) {
    auto creature = Director::buildCreature("TestCreature", 5, 5, 3, 1, 10);
    EXPECT_EQ(creature.get_name(), "TestCreature");
    EXPECT_EQ(creature.get_speed(), 5);
    EXPECT_EQ(creature.get_damage(), 5);
    EXPECT_EQ(creature.get_range(), 3);
    EXPECT_EQ(creature.get_type(), 1);
    EXPECT_EQ(creature.get_initiative(), 10);
}

TEST_F(DirectorTest, AbilityBuilding) {
    auto ability = Director::buildAbility("TestAbility", test_creature, 1, 50, 100, 1000);
    EXPECT_EQ(ability.get_name(), "TestAbility");
    EXPECT_EQ(ability.get_level(), 1);
    EXPECT_EQ(ability.get_energy(), 50);
    EXPECT_EQ(ability.get_experience(), 100);
    EXPECT_EQ(ability.get_hp(), 1000);
}

TEST_F(DirectorTest, SchoolBuilding) {
    auto school = Director::buildSchool("TestSchool", test_ability);
    EXPECT_EQ(school.get_name(), "TestSchool");
    EXPECT_FALSE(school.get_abilities().empty());
}

TEST_F(DirectorTest, EntityBuilding) {
    auto moral_troop = EntityDirector::createMoralTroop(test_ability, 50, 1);
    EXPECT_EQ(moral_troop.get_moral(), 50);
    EXPECT_EQ(moral_troop.get_id_summoner(), 1);

    auto amoral_troop = EntityDirector::createAmoralTroop(test_ability, 1);
    EXPECT_EQ(amoral_troop.get_id_summoner(), 1);

    auto summoner = EntityDirector::createSummoner(test_ability, 100, 10);
    EXPECT_EQ(summoner.get_max_energy(), 100);
    EXPECT_EQ(summoner.get_accum_index(), 10);
}
