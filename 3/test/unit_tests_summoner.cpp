#include <gtest/gtest.h>
#include "queue/entity/builder/entity_director.hpp"
#include "schools/builders/director.hpp"

class SummonerTest : public ::testing::Test {
  protected:
    static inline Creature test_creature = Director::buildCreature("TestCreature", 5, 5, 3, 1, 10);
    static inline Ability test_ability = Director::buildAbility("TestSummoner", test_creature, 1, 0, 0, 1000);
    Summoner* summoner{nullptr};

    static void
    SetUpTestSuite() {
        auto& schools = Schools::getInstance();
        auto school = Director::buildSchool("TestSchool", test_ability);
        schools.add_school(school);
    }

    void
    SetUp() override {
        summoner = new Summoner(EntityDirector::createSummoner(test_ability, 100, 10));
    }

    void
    TearDown() override {
        delete summoner;
        summoner = nullptr;
    }

    ~SummonerTest() override {
        if (summoner) {
            delete summoner;
            summoner = nullptr;
        }
    }
};

TEST_F(SummonerTest, Initialization) {
    EXPECT_EQ(summoner->get_max_energy(), 100);
    EXPECT_EQ(summoner->get_energy(), 100);
    EXPECT_EQ(summoner->get_accum_index(), 10);
    EXPECT_EQ(summoner->get_experience(), 0);
}

TEST_F(SummonerTest, EnergyManagement) {
    summoner->spend_energy(50);
    EXPECT_EQ(summoner->get_energy(), 50);

    summoner->accum_energy();
    EXPECT_EQ(summoner->get_energy(), 60);

    EXPECT_THROW(summoner->spend_energy(70), NotEnoughEnergyException);

    summoner->reset_energy();
    EXPECT_EQ(summoner->get_energy(), 100);
}

TEST_F(SummonerTest, ExperienceManagement) {
    summoner->add_experience(500);
    EXPECT_EQ(summoner->get_experience(), 500);

    // Get the first school safely
    const auto& schools = Schools::getInstance().get_schools();
    ASSERT_FALSE(schools.empty()) << "No schools available for testing";
    const auto& school = schools.front();

    EXPECT_THROW(summoner->upgrade_school(school, 1000), NotEnoughExperienceException);

    summoner->add_experience(1000);
    EXPECT_NO_THROW(summoner->upgrade_school(school, 1000));
    EXPECT_EQ(summoner->get_school_level(school.get_id()), 2);
}

TEST_F(SummonerTest, OwnershipManagement) {
    summoner->add_ownership(1);
    summoner->add_ownership(2);
    summoner->add_ownership(3);

    auto ownerships = summoner->get_ownerships();
    EXPECT_EQ(ownerships.size(), 3);
    EXPECT_TRUE(std::find(ownerships.begin(), ownerships.end(), 2) != ownerships.end());

    summoner->delete_ownership(2);
    ownerships = summoner->get_ownerships();
    EXPECT_EQ(ownerships.size(), 2);
    EXPECT_TRUE(std::find(ownerships.begin(), ownerships.end(), 2) == ownerships.end());
}

TEST_F(SummonerTest, SchoolLevels) {
    const auto& schools = Schools::getInstance().get_schools();
    for (const auto& school : schools) {
        EXPECT_EQ(summoner->get_school_level(school.get_id()), 1);
    }
}
