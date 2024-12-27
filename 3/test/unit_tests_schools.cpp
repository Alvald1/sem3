#include <gtest/gtest.h>

#include "schools/builders/director.hpp"
#include "schools/schools.hpp"

class SchoolsTest : public ::testing::Test {
  protected:
    Schools* schools = nullptr;
    Creature test_creature = Director::buildCreature("Test Creature", 5, 10, 2, 1, 3);
    Ability test_ability = Director::buildAbility("Test Ability", test_creature, 1, 50, 100, 200);
    School test_school = Director::buildSchool("Test School", test_ability);

    void
    SetUp() override {
        schools = &Schools::getInstance();
    }

    void
    TearDown() override {
        Schools::destroyInstance();
    }
};

TEST_F(SchoolsTest, SingletonInstance) {
    auto& instance1 = Schools::getInstance();
    auto& instance2 = Schools::getInstance();
    EXPECT_EQ(&instance1, &instance2);
}

TEST_F(SchoolsTest, AddAndCountSchools) {
    schools->add_school(test_school);
    EXPECT_EQ(schools->count_schools(), 1);

    School another_school("Another School");
    schools->add_school(another_school);
    EXPECT_EQ(schools->count_schools(), 2);
}

TEST_F(SchoolsTest, FindSchoolById) {
    schools->add_school(test_school);

    auto found = schools->find_school_by_id(test_school.get_id());
    EXPECT_TRUE(found.has_value());
    EXPECT_EQ(found->get().get_name(), "Test School");

    auto not_found = schools->find_school_by_id(999);
    EXPECT_FALSE(not_found.has_value());
}

TEST_F(SchoolsTest, FindSchoolByName) {
    schools->add_school(test_school);

    auto found = schools->find_school_by_name("Test School");
    EXPECT_TRUE(found.has_value());
    EXPECT_EQ(found->get().get_id(), test_school.get_id());

    auto not_found = schools->find_school_by_name("Non-existent School");
    EXPECT_FALSE(not_found.has_value());
}

TEST_F(SchoolsTest, RemoveSchool) {
    schools->add_school(test_school);
    EXPECT_TRUE(schools->remove_school(test_school.get_id()));
    EXPECT_EQ(schools->count_schools(), 0);
    EXPECT_FALSE(schools->remove_school(test_school.get_id()));
}

TEST_F(SchoolsTest, GetAvailableAbilities) {
    schools->add_school(test_school);

    std::unordered_map<size_t, size_t> levels;
    levels[test_school.get_id()] = 1;

    auto available = schools->get_available_abilities(levels, 50);
    EXPECT_EQ(available.size(), 1);

    available = schools->get_available_abilities(levels, 40);
    EXPECT_EQ(available.size(), 0);
}

TEST_F(SchoolsTest, FindSummonerAbilities) {
    // Create a summoner creature (type 0)
    Creature summoner = Director::buildCreature("Summoner", 1, 1, 1, 0, 1);
    Ability summoner_ability = Director::buildAbility("Summon", summoner, 1, 50, 100, 200);
    School summoner_school = Director::buildSchool("Summoner School", summoner_ability);

    schools->add_school(summoner_school);
    schools->add_school(test_school);

    auto summoner_abilities = schools->find_summoner_abilities();
    EXPECT_EQ(summoner_abilities.size(), 1);
    EXPECT_EQ(summoner_abilities[0].get().get_creature().get_type(), 0);
}

TEST_F(SchoolsTest, GetUpgradableAbilities) {
    schools->add_school(test_school);

    std::unordered_map<size_t, size_t> levels;
    levels[test_school.get_id()] = 1;

    auto upgradable = schools->get_upgradable_abilities(levels, 100);
    EXPECT_EQ(upgradable.size(), 1);

    upgradable = schools->get_upgradable_abilities(levels, 99);
    EXPECT_EQ(upgradable.size(), 0);
}
